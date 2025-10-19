import sys
from pathlib import Path

shader_path = sys.argv[1]
output_path = Path(sys.argv[2])
shader_name = output_path.name.split(".")[0]

with open(shader_path, "r") as f:
	shader_code = f.read()

# Null terminated for C style APIs, but also with a size variable for slice style APIs
with open(output_path, "w") as f:
	f.write("#include \"common.hpp\"\n")
	f.write(f"constexpr u8 {shader_name}[] = {{")
	for i, byte in enumerate(shader_code.encode("utf-8")):
		if i % 8 == 0:
			f.write("\n\t")
		f.write(str(byte) + ", ")
	f.write("0\n};\n")
	f.write(f"constexpr usize {shader_name}_length = sizeof({shader_name}) - 1;\n")
