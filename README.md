### Install CPython header files:

On Ubuntu/Debian:
```bash
sudo apt-get install python3-dev
```
On Fedora:
```bash
sudo dnf install python3-devel
```
On Arch Linux:
```bash
sudo pacman -S python
```

### Compile `python_caller.c` with `gcc`:

```bash
gcc -o python_caller python_caller.c -I/usr/include/python3.11/ -lpython3.11
```

### Run `python_caller`:

```bash
./python_caller <python_file> <function_name>
```