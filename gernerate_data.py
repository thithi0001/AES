from mylib import *

def generate_sample(samples):
    states = open("state_sample_data.txt", 'w')
    for _ in range(samples):
        states.write(vector_hex_to_hex_str(random_vector()) + "\n")

    print(f"{samples} samples had been created!")

def generate_sub_bytes():
    sb = open("sub_bytes_data.txt", 'w')
    states = open("state_sample_data.txt", 'r')
    for line in states:
        v = hex_str_to_vector_hex(line.rstrip("\n"))
        sb_block = sub_bytes(v)
        str_sb = vector_hex_to_hex_str(sb_block)
        sb.write(str_sb + "\n")
        
    print("All sub bytes had been created!")

def generate_mix_columns():
    mc = open("mix_columns_data.txt", 'w')
    states = open("state_sample_data.txt", 'r')
    for line in states:
        v = hex_str_to_vector_hex(line.rstrip("\n"))
        mc_block = mix_columns(v)
        str_mc = vector_hex_to_hex_str(mc_block)
        mc.write(str_mc + "\n")
        
    print("All mix columns had been created!")

# generate_sample(100)
# generate_sub_bytes()
# generate_mix_columns()