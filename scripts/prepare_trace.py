# Copyright (c) 2025 Antmicro <www.antmicro.com>
#
# SPDX-License-Identifier: Apache-2.0

"""
Script preparing trace (in TEF) based on the CTF trace and metadata, e.g. TFLM model.
"""

import argparse
import json
import os
import sys
from io import StringIO
from pathlib import Path

from ctf2tef import EventPhase, ctf_to_tef, prepare_dir


def tflm_name(msg):
    """
    Generates suffix for TFLM event name.
    """
    fields = msg.event.payload_field
    if not fields:
        return ""
    name = str(fields.get("tag", ""))
    if "subgraph_idx" in fields:
        name += f"_{fields['subgraph_idx']}"
    if "op_idx" in fields:
        name += f"_{fields['op_idx']}"
    return name


# The dictionary of custom events, where the key is a name of a resulting event,
# and values are tuples of received beginning and end events
# and the function extending the event name based on the arguments.
# If the events contain tag in the payload, it will be appended
# to the resulting event name.
CUSTOM_EVENTS = {
    "TFLM::": ("zpl_tflm_begin_event", "zpl_tflm_end_event", tflm_name),
}


def memory_name(msg):
    """
    Generates suffix for Memory event name.
    """
    if not (args := msg.event.payload_field):
        return ""
    try:
        # Get enum label and remove ZPL_ prefix
        return args["memory_region"].labels[0][4:]
    except Exception:
        return ""


# The dictionary of custom metadata events, where the key is CTF event name
# and values tuples of new event name and function producing name suffix.
CUSTOM_METADATA = {
    "zpl_memory_event": ("MEMORY::", memory_name),
}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        "prepare_trace",
        description=__doc__,
        allow_abbrev=False,
    )
    parser.add_argument(
        "ctf_trace",
        type=Path,
        help="The path to a trace in CTF format",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="The path to the output, if not provided, the results will be printed to STDOUT",
        default=None,
    )
    parser.add_argument(
        "--zephyr-base",
        type=Path,
        default=os.environ.get("ZEPHYR_BASE", None),
        help="The path to a Zephyr repository, can be passed with $ZEPHYR_BASE, "
        "otherwise will be deduced based on the script path",
    )
    parser.add_argument(
        "--tflm-model-path",
        type=Path,
        help="Path to the required model, extracted information will be appedened "
        "to the final trace as a metadata",
        default=None,
    )
    args = parser.parse_args(sys.argv[1:])

    tef_trace_io = StringIO()
    with prepare_dir(args.ctf_trace, args.zephyr_base) as tmp_dir:
        tef_trace = ctf_to_tef(str(tmp_dir), False, CUSTOM_METADATA, CUSTOM_EVENTS)

    if args.tflm_model_path is not None:
        from extract_tflite_model_data import extract_model_data

        tflm_model_data = extract_model_data(args.tflm_model_path)
        tef_trace.insert(
            0,
            {
                "name": "TFLM::MODEL",
                "cat": "zephyr",
                "ph": EventPhase.METADATA.value,
                "pid": 0,
                "tid": 0,
                "ts": 0,
                "args": tflm_model_data,
            },
        )

    if args.output is not None:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        with args.output.open("w") as fd:
            json.dump(tef_trace, fd)
    else:
        print(json.dumps(tef_trace, indent=2))
