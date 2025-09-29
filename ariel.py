import streamlit as st
import numpy as np
import pandas as pd
import plotly.graph_objects as go
from assets import show_brand_logo




def caesar_encrypt(plaintext, shift): 
    result = ""
    for char in plaintext: 
        if char.isupper(): 
            result += chr((ord(char) + shift - 65) % 26 + 65)
        elif char.islower():
            result += chr((ord (char) + shift - 97) % 26 + 97)
        else: 
            result += char
    return result   




def caesar_decrypt(ciphertext, shift):
    result = ""
    for char in ciphertext:
        if char.isupper():
            result += chr((ord(char) - shift - 65) % 26 + 65)
        elif char.islower():
            result += chr((ord(char) - shift - 97) % 26 + 97)
        else:
            result += char
    return result



