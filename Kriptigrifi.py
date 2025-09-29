import streamlit as st

# -----------------------------
# Caesar Cipher
# -----------------------------
def caesar_cipher(text, key, mode="encrypt"):
    result = ""
    if mode == "decrypt":
        key = 26 - (key % 26)
    for char in text:
        if char.isupper():
            result += chr((ord(char) - 65 + key) % 26 + 65)
        elif char.islower():
            result += chr((ord(char) - 97 + key) % 26 + 97)
        else:
            result += char
    return result

# -----------------------------
# Rail Fence Cipher
# -----------------------------
def railfence_encrypt(text, key):
    rail = [["\n" for _ in range(len(text))] for _ in range(key)]
    dir_down = False
    row, col = 0, 0
    for char in text:
        if row == 0 or row == key - 1:
            dir_down = not dir_down
        rail[row][col] = char
        col += 1
        row += 1 if dir_down else -1
    return "".join(char for r in rail for char in r if char != "\n")

def railfence_decrypt(cipher, key):
    rail = [["\n" for _ in range(len(cipher))] for _ in range(key)]
    dir_down = None
    row, col = 0, 0
    for _ in range(len(cipher)):
        if row == 0:
            dir_down = True
        if row == key - 1:
            dir_down = False
        rail[row][col] = "*"
        col += 1
        row += 1 if dir_down else -1
    index = 0
    for i in range(key):
        for j in range(len(cipher)):
            if rail[i][j] == "*" and index < len(cipher):
                rail[i][j] = cipher[index]
                index += 1
    result, row, col = [], 0, 0
    for _ in range(len(cipher)):
        if row == 0:
            dir_down = True
        if row == key - 1:
            dir_down = False
        if rail[row][col] != "*":
            result.append(rail[row][col])
            col += 1
        row += 1 if dir_down else -1
    return "".join(result)

# -----------------------------
# Stream Cipher (XOR)
# -----------------------------
def stream_cipher(text, key):
    return "".join(chr(ord(text[i]) ^ ord(key[i % len(key)])) for i in range(len(text)))

def to_hex(s):
    return "".join(f"{ord(c):02X}" for c in s)

def from_hex(h):
    return "".join(chr(int(h[i:i+2], 16)) for i in range(0, len(h), 2))

# -----------------------------
# Block Cipher sederhana
# -----------------------------
def block_cipher_encrypt(text, key):
    return "".join(chr((ord(text[i]) + ord(key[i % len(key)])) % 256) for i in range(len(text)))

def block_cipher_decrypt(text, key):
    return "".join(chr((ord(text[i]) - ord(key[i % len(key)]) + 256) % 256) for i in range(len(text)))

# -----------------------------
# Super Enkripsi
# -----------------------------
def super_encrypt(text, key_caesar, key_rail, key_stream, key_block):
    step1 = caesar_cipher(text, key_caesar, "encrypt")
    step2 = railfence_encrypt(step1, key_rail)
    step3 = stream_cipher(step2, key_stream)
    step4 = block_cipher_encrypt(step3, key_block)
    return to_hex(step4)

def super_decrypt(cipher_hex, key_caesar, key_rail, key_stream, key_block):
    step4 = block_cipher_decrypt(from_hex(cipher_hex), key_block)
    step3 = stream_cipher(step4, key_stream)
    step2 = railfence_decrypt(step3, key_rail)
    step1 = caesar_cipher(step2, key_caesar, "decrypt")
    return step1

# -----------------------------
# Streamlit UI
# -----------------------------
st.title("🔐 Program Enkripsi dan Dekripsi Pesan")

menu = st.sidebar.selectbox(
    "Pilih Algoritma",
    ["Caesar Cipher", "Rail Fence Cipher", "Stream Cipher (XOR)", "Block Cipher", "Super Enkripsi"]
)

if menu == "Caesar Cipher":
    st.header("Caesar Cipher")
    mode = st.radio("Mode", ["Enkripsi", "Dekripsi"])
    teks = st.text_area("Masukkan teks")
    key = st.number_input("Kunci (angka)", min_value=1, max_value=25, value=3)
    if st.button("Proses"):
        if mode == "Enkripsi":
            st.success(caesar_cipher(teks, key, "encrypt"))
        else:
            st.success(caesar_cipher(teks, key, "decrypt"))

elif menu == "Rail Fence Cipher":
    st.header("Rail Fence Cipher")
    mode = st.radio("Mode", ["Enkripsi", "Dekripsi"])
    teks = st.text_area("Masukkan teks")
    key = st.number_input("Kunci (angka)", min_value=2, value=2)
    if st.button("Proses"):
        if mode == "Enkripsi":
            st.success(railfence_encrypt(teks, key))
        else:
            st.success(railfence_decrypt(teks, key))

elif menu == "Stream Cipher (XOR)":
    st.header("Stream Cipher (XOR)")
    mode = st.radio("Mode", ["Enkripsi", "Dekripsi"])
    teks = st.text_area("Masukkan teks" if mode == "Enkripsi" else "Masukkan cipher (hex)")
    key = st.text_input("Kunci (teks)")
    if st.button("Proses"):
        if not key:
            st.error("Kunci tidak boleh kosong")
        else:
            if mode == "Enkripsi":
                cipher = stream_cipher(teks, key)
                st.success(to_hex(cipher))
            else:
                try:
                    plain = stream_cipher(from_hex(teks), key)
                    st.success(plain)
                except:
                    st.error("Format hex tidak valid")

elif menu == "Block Cipher":
    st.header("Block Cipher (Sederhana)")
    mode = st.radio("Mode", ["Enkripsi", "Dekripsi"])
    teks = st.text_area("Masukkan teks" if mode == "Enkripsi" else "Masukkan cipher (hex)")
    key = st.text_input("Kunci (teks)")
    if st.button("Proses"):
        if not key:
            st.error("Kunci tidak boleh kosong")
        else:
            if mode == "Enkripsi":
                cipher = block_cipher_encrypt(teks, key)
                st.success(to_hex(cipher))
            else:
                try:
                    plain = block_cipher_decrypt(from_hex(teks), key)
                    st.success(plain)
                except:
                    st.error("Format hex tidak valid")

elif menu == "Super Enkripsi":
    st.header("Super Enkripsi (Gabungan)")
    mode = st.radio("Mode", ["Enkripsi", "Dekripsi"])
    if mode == "Enkripsi":
        teks = st.text_area("Masukkan teks")
    else:
        teks = st.text_area("Masukkan cipher (hex)")
    key_caesar = st.number_input("Kunci Caesar (angka)", min_value=1, max_value=25, value=3)
    key_rail = st.number_input("Kunci Rail Fence (angka)", min_value=2, value=2)
    key_stream = st.text_input("Kunci Stream (teks)")
    key_block = st.text_input("Kunci Block (teks)")
    if st.button("Proses"):
        if not key_stream or not key_block:
            st.error("Kunci tidak boleh kosong")
        else:
            if mode == "Enkripsi":
                st.success(super_encrypt(teks, key_caesar, key_rail, key_stream, key_block))
            else:
                try:
                    st.success(super_decrypt(teks, key_caesar, key_rail, key_stream, key_block))
                except:
                    st.error("Dekripsi gagal. Periksa input atau kunci.")