#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ---------- GPIO PINS ----------

#define BUTTON_PIN 14

#define LED_NORMAL_PIN 15
#define LED_HEAT_PIN 16
#define LED_TYPHOON_PIN 17

#define BUZZER_PIN 18

// ---------- LDR / ADC ----------

#define LDR_ADC_PIN 26
#define LDR_ADC_CHANNEL 0

// ---------- THERMISTOR / ADC ----------

#define THERM_ADC_PIN 27
#define THERM_ADC_CHANNEL 1

// ---------- LIGHT HYSTERESIS THRESHOLDS ----------

#define LOW_ENTER_THRESHOLD 700
#define LOW_EXIT_THRESHOLD 900

#define HIGH_ENTER_THRESHOLD 2500
#define HIGH_EXIT_THRESHOLD 2200

// ---------- TEMPERATURE HYSTERESIS THRESHOLDS ----------

#define TEMP_HIGH_ENTER_THRESHOLD 2200
#define TEMP_HIGH_EXIT_THRESHOLD 2000

// ---------- I2C LCD ----------

#define I2C_PORT i2c0
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5
#define LCD_ADDR 0x27

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_COMMAND   0x00
#define LCD_CHARACTER 0x01

// ---------- TIMING ----------

#define BUZZER_INTERVAL_MS 1500
#define BLINK_INTERVAL_MS 300
#define LCD_UPDATE_INTERVAL_MS 500
#define SERIAL_PRINT_INTERVAL_MS 1000

// ---------- TYPES ----------

typedef enum {
    MODE_NORMAL = 0,
    MODE_URBAN_HEAT = 1,
    MODE_TYPHOON_ALERT = 2
} SystemMode;

typedef enum {
    LIGHT_LOW = 0,
    LIGHT_NORMAL = 1,
    LIGHT_HIGH = 2
} LightLevel;

// ---------- LCD FUNCTIONS ----------

void lcd_write_byte(uint8_t data) {
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &data, 1, false);
}

void lcd_toggle_enable(uint8_t data) {
    lcd_write_byte(data | LCD_ENABLE);
    sleep_us(500);

    lcd_write_byte(data & ~LCD_ENABLE);
    sleep_us(500);
}

void lcd_send_nibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble & 0xF0) | LCD_BACKLIGHT | mode;

    lcd_write_byte(data);
    lcd_toggle_enable(data);
}

void lcd_send_byte(uint8_t value, uint8_t mode) {
    lcd_send_nibble(value & 0xF0, mode);
    lcd_send_nibble((value << 4) & 0xF0, mode);
}

void lcd_command(uint8_t command) {
    lcd_send_byte(command, LCD_COMMAND);
}

void lcd_char(char character) {
    lcd_send_byte(character, LCD_CHARACTER);
}

void lcd_clear() {
    lcd_command(0x01);
    sleep_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40};

    lcd_command(0x80 | (row_offsets[row] + col));
}

void lcd_print_padded(const char *text) {
    int count = 0;

    while (*text && count < 16) {
        lcd_char(*text++);
        count++;
    }

    while (count < 16) {
        lcd_char(' ');
        count++;
    }
}

void lcd_init() {
    sleep_ms(50);

    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_ms(5);

    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_us(150);

    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_us(150);

    lcd_send_nibble(0x20, LCD_COMMAND);
    sleep_us(150);

    lcd_command(0x28); // 4-bit mode, 2 lines, 5x8 font
    lcd_command(0x0C); // display ON, cursor OFF
    lcd_command(0x06); // entry mode
    lcd_clear();
}

// ---------- TEXT HELPERS ----------

const char* mode_to_short_text(SystemMode mode) {
    if (mode == MODE_NORMAL) {
        return "NORMAL";
    }

    if (mode == MODE_URBAN_HEAT) {
        return "HEAT";
    }

    return "TYPHOON";
}

const char* light_to_short_text(LightLevel light_level) {
    if (light_level == LIGHT_LOW) {
        return "LOW";
    }

    if (light_level == LIGHT_NORMAL) {
        return "NORM";
    }

    return "HIGH";
}

// ---------- ADC FUNCTIONS ----------

uint16_t read_adc_average(uint adc_channel) {
    uint32_t sum = 0;

    adc_select_input(adc_channel);

    for (int i = 0; i < 16; i++) {
        sum += adc_read();
        sleep_ms(2);
    }

    return sum / 16;
}

uint16_t read_light_average() {
    return read_adc_average(LDR_ADC_CHANNEL);
}

uint16_t read_thermistor_average() {
    return read_adc_average(THERM_ADC_CHANNEL);
}

// ---------- LIGHT CLASSIFICATION ----------

LightLevel update_light_level(uint16_t light_raw, LightLevel previous_level) {
    if (previous_level == LIGHT_LOW) {
        if (light_raw > LOW_EXIT_THRESHOLD) {
            if (light_raw > HIGH_ENTER_THRESHOLD) {
                return LIGHT_HIGH;
            }

            return LIGHT_NORMAL;
        }

        return LIGHT_LOW;
    }

    if (previous_level == LIGHT_HIGH) {
        if (light_raw < HIGH_EXIT_THRESHOLD) {
            if (light_raw < LOW_ENTER_THRESHOLD) {
                return LIGHT_LOW;
            }

            return LIGHT_NORMAL;
        }

        return LIGHT_HIGH;
    }

    if (light_raw < LOW_ENTER_THRESHOLD) {
        return LIGHT_LOW;
    }

    if (light_raw > HIGH_ENTER_THRESHOLD) {
        return LIGHT_HIGH;
    }

    return LIGHT_NORMAL;
}

// ---------- TEMPERATURE CLASSIFICATION ----------

bool update_temp_high(uint16_t temp_raw, bool previous_temp_high) {
    if (previous_temp_high) {
        if (temp_raw < TEMP_HIGH_EXIT_THRESHOLD) {
            return false;
        }

        return true;
    }

    if (temp_raw > TEMP_HIGH_ENTER_THRESHOLD) {
        return true;
    }

    return false;
}

// ---------- OUTPUT FUNCTIONS ----------

void turn_off_all_leds() {
    gpio_put(LED_NORMAL_PIN, 0);
    gpio_put(LED_HEAT_PIN, 0);
    gpio_put(LED_TYPHOON_PIN, 0);
}

void beep_short() {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(120);
    gpio_put(BUZZER_PIN, 0);
}

void show_steady_mode(SystemMode mode) {
    turn_off_all_leds();

    if (mode == MODE_NORMAL) {
        gpio_put(LED_NORMAL_PIN, 1);
    }
    else if (mode == MODE_URBAN_HEAT) {
        gpio_put(LED_HEAT_PIN, 1);
    }
    else if (mode == MODE_TYPHOON_ALERT) {
        gpio_put(LED_TYPHOON_PIN, 1);
    }
}

void update_alert_output(SystemMode mode, bool blink_state) {
    turn_off_all_leds();

    if (mode == MODE_URBAN_HEAT) {
        gpio_put(LED_HEAT_PIN, blink_state);
    }
    else if (mode == MODE_TYPHOON_ALERT) {
        gpio_put(LED_TYPHOON_PIN, blink_state);
    }
}

bool is_alert_condition(SystemMode mode, LightLevel light_level, bool temp_high) {
    if (mode == MODE_URBAN_HEAT) {
        if (light_level == LIGHT_HIGH || temp_high) {
            return true;
        }
    }

    if (mode == MODE_TYPHOON_ALERT && light_level == LIGHT_LOW) {
        return true;
    }

    return false;
}

void update_lcd(SystemMode mode, uint16_t light_raw, uint16_t temp_raw, bool alert_active) {
    char line1[17];
    char line2[17];

    snprintf(line1, sizeof(line1), "MODE:%-10s", mode_to_short_text(mode));

    snprintf(line2, sizeof(line2), "L%04u T%04u %s",
             light_raw,
             temp_raw,
             alert_active ? "ALRT" : "OK");

    lcd_set_cursor(0, 0);
    lcd_print_padded(line1);

    lcd_set_cursor(1, 0);
    lcd_print_padded(line2);
}

// ---------- MAIN ----------

int main() {
    stdio_init_all();
    sleep_ms(2000);

    printf("Pico Resilience Monitor started\n");

    // Button
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // LEDs
    gpio_init(LED_NORMAL_PIN);
    gpio_set_dir(LED_NORMAL_PIN, GPIO_OUT);

    gpio_init(LED_HEAT_PIN);
    gpio_set_dir(LED_HEAT_PIN, GPIO_OUT);

    gpio_init(LED_TYPHOON_PIN);
    gpio_set_dir(LED_TYPHOON_PIN, GPIO_OUT);

    // Buzzer
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);

    // ADC
    adc_init();

    adc_gpio_init(LDR_ADC_PIN);
    adc_gpio_init(THERM_ADC_PIN);

    // I2C + LCD
    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    lcd_init();

    // State
    SystemMode current_mode = MODE_NORMAL;
    LightLevel current_light_level = LIGHT_NORMAL;

    bool current_temp_high = false;
    bool last_button_state = true;
    bool blink_state = false;

    uint32_t last_blink_time = to_ms_since_boot(get_absolute_time());
    uint32_t last_buzzer_time = to_ms_since_boot(get_absolute_time());
    uint32_t last_lcd_time = to_ms_since_boot(get_absolute_time());
    uint32_t last_print_time = to_ms_since_boot(get_absolute_time());

    show_steady_mode(current_mode);

    while (true) {
        uint32_t now = to_ms_since_boot(get_absolute_time());

        // ---------- BUTTON HANDLING ----------
        bool current_button_state = gpio_get(BUTTON_PIN);

        if (last_button_state == true && current_button_state == false) {
            sleep_ms(50);

            if (gpio_get(BUTTON_PIN) == false) {
                current_mode = (SystemMode)((current_mode + 1) % 3);

                blink_state = false;
                show_steady_mode(current_mode);
                beep_short();

                while (gpio_get(BUTTON_PIN) == false) {
                    sleep_ms(10);
                }
            }
        }

        last_button_state = current_button_state;

        // ---------- SENSOR READINGS ----------
        uint16_t light_raw = read_light_average();
        uint16_t temp_raw = read_thermistor_average();

        current_light_level = update_light_level(light_raw, current_light_level);
        current_temp_high = update_temp_high(temp_raw, current_temp_high);

        bool alert_active = is_alert_condition(
            current_mode,
            current_light_level,
            current_temp_high
        );

        // ---------- ALERT OUTPUT ----------
        if (alert_active) {
            if (now - last_blink_time >= BLINK_INTERVAL_MS) {
                blink_state = !blink_state;
                update_alert_output(current_mode, blink_state);
                last_blink_time = now;
            }

            if (now - last_buzzer_time >= BUZZER_INTERVAL_MS) {
                beep_short();
                last_buzzer_time = now;
            }
        } else {
            show_steady_mode(current_mode);
            gpio_put(BUZZER_PIN, 0);
        }

        // ---------- LCD UPDATE ----------
        if (now - last_lcd_time >= LCD_UPDATE_INTERVAL_MS) {
            update_lcd(current_mode, light_raw, temp_raw, alert_active);
            last_lcd_time = now;
        }

        // ---------- SERIAL DEBUG ----------
        if (now - last_print_time >= SERIAL_PRINT_INTERVAL_MS) {
            printf("Mode: %s | Light ADC: %u | Light: %s | Temp ADC: %u | Temp: %s | Alert: %s\n",
                   mode_to_short_text(current_mode),
                   light_raw,
                   light_to_short_text(current_light_level),
                   temp_raw,
                   current_temp_high ? "HIGH" : "NORM",
                   alert_active ? "ACTIVE" : "OFF");

            last_print_time = now;
        }

        sleep_ms(10);
    }

    return 0;
}