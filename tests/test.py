import random
import string
import base64


def make_random_text(length):
    chars = string.printable
    text = ''
    for _ in range(length):
        text += random.choice(chars)
    return text


def test_encode_decode(text):
    encoded = base64.a85encode(text.encode()).decode('ascii')
    decoded = base64.a85decode(encoded).decode('utf-8')
    return decoded == text

def test_random_texts():
    test_count = 47
    max_length = 100
    for _ in range(test_count):
        length = random.randint(1, max_length)
        text = make_random_text(length)
        if not test_encode_decode(text):
            print(f"Ошибка для: {text}")
            return False
    
    return True

def test_special_cases():

    special_texts = [
        "",       # Пустой текст
        "a",      # Один символ
        "~"*100,  # Много спецсимволов
        "Hello"   # Обычное слово
    ]
    
    for text in special_texts:
        if not test_encode_decode(text):
            print(f"Ошибка для : {text}")
            return False
    
    return True


def main():
    print("Начинаем тестирование...")
    
    print("\nТест 1: Случайные тексты")
    test_random_texts()
    
    print("\nТест 2: Особые случаи")
    test_special_cases()
    
    print("\nВсе тесты завершены!")

# Запускаем программу
if __name__ == "__main__":
    main()
