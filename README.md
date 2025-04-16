# Pi Digit Checker

Bu program, pi sayısının ilk 1 milyon basamağı içinde belirli bir sayı dizisini arar.

## Gereksinimler

- C++ derleyici (g++)
- libcurl kütüphanesi
- make

## Kurulum

macOS için libcurl kurulumu:

```bash
brew install curl
```

## Kullanım

1. `check.txt` dosyasına aranacak sayıyı yazın
2. Programı derlemek için:
   ```bash
   make
   ```
3. Programı çalıştırmak için:
   ```bash
   ./pi_checker
   ```

## Temizlik

Derlenen dosyaları temizlemek için:

```bash
make clean
```
