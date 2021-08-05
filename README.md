# `aqi-c`

A small C library to convert pollutant concentration to AQI.

Supported pollutants are:

- PM 2.5
- PM 10.0

## Usage in `esphome`

Here is an example usage in `esphome`. The sensor is `SDS011`, and the device
is a generic `nodemcu` board. The device reports raw pollutant values, AQI
values of the pollutants, the combined AQI value, and the category of the AQI
value for human being.

Clone the repository:

```console
mkdir config/include
cd config/include
git clone https://github.com/trombik/aqi-c
cd -
```
Copy [`esphome-example/config/example.yaml`](esphome-example/config/example.yaml)
to your configuration directory.

Build the example:

```console
esphome compile config/example.yaml
```

## References

* [Air Quality Index (AQI)](https://www.epa.gov/sites/default/files/2014-05/documents/zell-aqi.pdf)
* [REVISED AIR QUALITY STANDARDS FOR PARTICLE POLLUTION AND UPDATES TO THE AIR QUALITY INDEX (AQI)](https://www.epa.gov/sites/default/files/2016-04/documents/2012_aqi_factsheet.pdf) (page 4)
