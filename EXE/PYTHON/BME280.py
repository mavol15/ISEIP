#!/usr/bin/env python

from Adafruit_BME280 import *
import MySQLdb as dbapi

dbServer='localhost'
dbPass='2imprezsAutoPWD'
dbUser='AutoUser'
dbDatabase='sensorDB'

db = dbapi.connect(host=dbServer, user=dbUser, passwd=dbPass, db=dbDatabase)
x = db.cursor()

sensor = BME280(t_mode=BME280_OSAMPLE_16, p_mode=BME280_OSAMPLE_16, h_mode=BME280_OSAMPLE_16, busnum=2)

temperature = sensor.read_temperature()
pressure = sensor.read_pressure()
hectopascals = pascals / 100
humidity = sensor.read_humidity()


#print 'Temp      = {0:0.3f} deg C'.format(degrees)
#print 'Pressure  = {0:0.2f} hPa'.format(hectopascals)
#print 'Humidity  = {0:0.2f} %'.format(humidity)

try:
    sensor.get_sensor_data()
    out_to_db = "INSERT INTO sensorDB.sensorTB (sensorTB.time, sensorTB.temp, sensorTB.pres, sensorTB.hum) VALUES (NOW() - INTERVAL MOD((EXTRACT(SECOND FROM NOW())), 10) SECOND,{0:.2f}, {1:.1f}, {2:.2f}) ON DUPLICATE KEY UPDATE sensorTB.temp = {0:.2f}, sensorTB.pres = {1:.1f}, sensorTB.hum = {2:.2f};".format(temperature, pressure, humidity)
    try:
        x.execute(out_to_db)
        db.commit()
    except:
        db.rollback()
    db.close()

except KeyboardInterrupt:
    db.close()
    pass
