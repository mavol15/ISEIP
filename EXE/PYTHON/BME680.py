#!/usr/bin/env python

import os
import bme680
import time
import MySQLdb as dbapi

dbServer='localhost'
dbPass='2imprezsAutoPWD'
dbUser='AutoUser'
dbDatabase='sensorDB'

db = dbapi.connect(host=dbServer, user=dbUser, passwd=dbPass, db=dbDatabase)
x = db.cursor()
#print("MySQL/MariaDB init Complete")


import smbus
i2cbus = smbus.SMBus(2)
sensor = bme680.BME680(i2c_addr=0x77, i2c_device=i2cbus)

#print("I2C Init Complete")

# These oversampling settings can be tweaked to
# change the balance between accuracy and noise in
# the data.
if not os.path.isfile('PYTHON_INIT'):
#    print("Running IF NOT code")
    sensor.set_humidity_oversample(bme680.OS_4X)
    sensor.set_pressure_oversample(bme680.OS_8X)
    sensor.set_temperature_oversample(bme680.OS_8X)
    sensor.set_filter(bme680.FILTER_SIZE_3)
    sensor.set_gas_status(bme680.DISABLE_GAS_MEAS)

    for name in dir(sensor.data):
        value = getattr(sensor.data, name)

#    sensor.set_gas_heater_temperature(320)
#    sensor.set_gas_heater_duration(150)
#    sensor.select_gas_heater_profile(0)

    os.mknod('PYTHON_INIT')

# Up to 10 heater profiles can be configured, each
# with their own temperature and duration.
# sensor.set_gas_heater_profile(200, 150, nb_profile=1)
# sensor.select_gas_heater_profile(1)

try:
    sensor.get_sensor_data()
    out_to_db = "INSERT INTO sensorDB.sensorTB (sensorTB.time, sensorTB.temp, sensorTB.pres, sensorTB.hum) VALUES (NOW() - INTERVAL MOD((EXTRACT(SECOND FROM NOW())), 10) SECOND,{0:.2f}, {1:.1f}, {2:.2f}) ON DUPLICATE KEY UPDATE sensorTB.temp = {0:.2f}, sensorTB.pres = {1:.1f}, sensorTB.hum = {2:.2f};".format(sensor.data.temperature, sensor.data.pressure, sensor.data.humidity)
    try:
        x.execute(out_to_db)
        db.commit()
    except:
        db.rollback()
    db.close()

except KeyboardInterrupt:
    db.close()
    pass
