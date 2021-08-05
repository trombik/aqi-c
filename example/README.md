# Example

An example to show AQI of PM 2.5.

## Requirements

* C compiler
* `make(1)`, either BSD or GNU

## Building

```console
cd src
make
```

## Usage

the first argument is pollutant (PM 2.5) concentration in `µg/m³`.

```console
> ./example 100.29
AQI (PM 2.5): 174
```
