"""ZPL West extension for tracing data capture."""

import subprocess
from textwrap import dedent

import serial
from west.commands import WestCommand


class ZplGdbCapture(WestCommand):
    """Main class for the zpl-gdb-capture command."""

    def __init__(self):
        """Init function for the zpl-gdb-capture command."""
        super().__init__(
            "zpl-gdb-capture",
            "Capture traces using GDB",
            dedent("""
                Capture traces using GDB.

                This command captures traces using GDB from RAM using the `dump` command."""),
        )

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name, help=self.help, description=self.description)

        parser.add_argument("elf_path", help="Zephyr ELF path")
        parser.add_argument("output_path", help="Capture output path")

        return parser

    def do_run(self, args, unknown_args):
        self.inf(f"Capturing traces to {args.output_path}...")

        cmd = [
            "gdb-multiarch",
            "-batch",
            "-ex",
            "set pagination off",
            "-ex",
            "target remote :3333",
            "-ex",
            "set $start = &ram_tracing",
            "-ex",
            "set $end = (char*)&ram_tracing + sizeof(ram_tracing)",
            "-ex",
            f"dump binary memory {args.output_path} $start $end",
            "-ex",
            "quit",
            args.elf_path,
        ]

        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        (output, _) = proc.communicate()
        exit_code = proc.wait()

        if exit_code != 0:
            self.err(output)
            self.die("Failed to capture tracing data!")


class ZplUartCapture(WestCommand):
    """Main class for the zpl-uart-capture command."""

    def __init__(self):
        """Init function for the zpl-uart-capture command."""
        super().__init__(
            "zpl-uart-capture",
            "Capture traces using UART",
            dedent("""
                Capture traces using UART.

                This command capures traces using the serial interface."""),
        )

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name, help=self.help, description=self.description)

        parser.add_argument("serial_port", help="Seral port")
        parser.add_argument("serial_baudrate", help="Seral baudrate")
        parser.add_argument("output_path", help="Capture output path")

        return parser

    def do_run(self, args, unknown_args):
        ser = serial.Serial(args.serial_port, args.serial_baudrate)
        if ser.is_open:
            self.inf(f"Capturing traces on {ser.port}@{ser.baudrate}...")
            self.inf("Press C-c to stop.")
        else:
            self.die(f"Couldn't open port {ser.port}!")

        ser.write("enable\r".encode())

        with open(args.output_path, "wb") as f:
            while True:
                try:
                    while ser.inWaiting() > 0:
                        f.write(ser.read())
                except KeyboardInterrupt:
                    break

        ser.close()
