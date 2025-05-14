# Zephyr AI Profiling Library

This repository hosts sources of the Zephyr AI Profiling Library.

## Getting started

Install `west` with `pip`:

<!-- name="pip-init" -->
```shell
pip install -r requirements.txt
```

Then, initialize the workspace using `west`:

<!-- name="west-init" -->
```shell
west init -l .
west update
west zephyr-export
west packages pip --install
west sdk install
```

## Building samples

Run the following command:
<!-- name="build-samples -->
```shell
west build -p -b max78002evkit_custom/max78002/m4 samples/trace/named_event
```
