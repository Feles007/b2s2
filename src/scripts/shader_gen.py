import sys
from pathlib import Path

output_path = Path(sys.argv[1])

shader_paths = sys.argv[2:]

shader_sources = []
for shader_path in shader_paths:
	with open(shader_path, "r") as f:
		shader_code = f.read()

	shader_name = Path(shader_path).stem

	shader_sources.append((shader_name, shader_code))

# Null terminated for C style APIs, but also with a size variable for slice style APIs
with open(output_path, "w") as f:
	f.write("#include \"common.hpp\"\n")
	f.write("namespace shader {\n")

	for shader_name, shader_code in shader_sources:
		f.write(f"\tconstexpr char {shader_name}_src[] = {{")
		for i, byte in enumerate(shader_code.encode("utf-8")):
			f.write(str(byte) + ", ")
		f.write("0};\n")
		f.write(f"\tconstexpr usize {shader_name}_length = sizeof({shader_name}_src) - 1;\n")

	f.write("}\n")
