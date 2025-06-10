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
west patch apply
west zephyr-export
west packages pip --install
west sdk install
```

## Building samples

Run the following command:
<!-- name="build-samples -->
```shell
west build -p -b max78002evkit/max78002/m4 samples/trace/named_event
```

## Convert the trace

The library produces traces in CTF (Common Trace Format), which in order to be visualized, have to be converted to TEF (Trace Event Format).

This can be achieved with [prepare_trace.py](./scripts/prepare_trace.py) script, which automatically prepares an environment (with combined metadata from Zephyr and Zephyr AI Profiling Lib, defining available events), converts the trace and processes custom event:

```bash
python3 ./scripts/prepare_trace.py [-h] [-o OUTPUT] [--zephyr-base ZEPHYR_BASE] [--tflm-model-path TFLM_MODEL_PATH] ctf_trace
```
