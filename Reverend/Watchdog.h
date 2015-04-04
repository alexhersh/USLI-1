void feed_watchdog_cb(unsigned long time) {
  wdt_reset();
}
