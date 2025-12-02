/*
 * SPDX-License-Identifier: Apache-2.0
 * LED Blink Application for FRDM-MCXA153
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Sleep time between LED toggles (in milliseconds) */
#define SLEEP_TIME_MS   1000

/* Get LED0 configuration from devicetree */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;

	/* Check if the LED device is ready */
	if (!gpio_is_ready_dt(&led)) {
		return -1;
	}

	/* Configure the LED GPIO pin as output */
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	/* Main loop: toggle LED on and off */
	while (1) {
		/* Toggle the LED state */
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return -1;
		}

		/* Wait before toggling again */
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}
