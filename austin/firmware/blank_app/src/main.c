/*
 * blank_app - the minimal starting point for your own firmware on either
 * board. Blinks the red status LED (led1 - NOT led0, which is a known
 * "doesn't visibly light" pin documented elsewhere in this repo) and,
 * on Argon, the breadboard LED on D5. Prints a heartbeat over USB-CDC
 * once a second.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(blank_app, LOG_LEVEL_INF);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

#if DT_NODE_EXISTS(DT_ALIAS(d5led))
static const struct gpio_dt_spec d5_led = GPIO_DT_SPEC_GET(DT_ALIAS(d5led), gpios);
#endif

int main(void)
{
	int err;
	uint32_t count = 0;

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("LED device not ready");
		return -ENODEV;
	}

	err = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (err) {
		LOG_ERR("Failed to configure LED (err %d)", err);
		return err;
	}

#if DT_NODE_EXISTS(DT_ALIAS(d5led))
	if (!gpio_is_ready_dt(&d5_led)) {
		LOG_ERR("D5 LED device not ready");
		return -ENODEV;
	}
	err = gpio_pin_configure_dt(&d5_led, GPIO_OUTPUT_ACTIVE);
	if (err) {
		LOG_ERR("Failed to configure D5 LED (err %d)", err);
		return err;
	}
#endif

	LOG_INF("blank_app ready - this is the minimal starting point");

	while (1) {
		gpio_pin_toggle_dt(&led);
#if DT_NODE_EXISTS(DT_ALIAS(d5led))
		gpio_pin_toggle_dt(&d5_led);
#endif
		LOG_INF("heartbeat %u", count++);
		k_sleep(K_SECONDS(1));
	}

	return 0;
}
