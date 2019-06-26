# storage_size

storage_size provides a small wrapper around storage sizes such as, for example, KiB, MiB and GiB.

## Usage
### Every day usage
```cpp
void set_size(sz::kibibytes size) {
    /* Do stuff */
}

int main() {
    sz::mebibytes mb_size = 1024_KiB;
    set_size(mb_size); // Seamless conversion from MiB to KiB
    
    sz::tebibytes tb_size = mb_size;
    
    // Byte count is always the same
    assert(mb_size.byte_count() == 1024 * 1024);
    assert(tb_size.byte_count() == mb_size.byte_count());
    
    // 'Unit' obviously differs between the different representations
    std::cout << "1024 KiB is " << mb_size.unit() << " in MiB" << std::endl;
    std::cout << "1024 KiB is " << tb_size.unit() << " in TiB" << std::endl;
}
```

### Adding other sizes
You can of course specify your own storage size
```cpp
using pib = std::ratio<1024 * 1024 * 1024 * 1024 * 1024, 1>;
using pebibytes = sz::storage_size<pib>;
```
