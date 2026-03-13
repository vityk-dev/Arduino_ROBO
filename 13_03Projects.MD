# 🚀 Zaawansowane Laboratoria Arduino: Projektowanie Asynchroniczne

**⏱ Czas na projekt:** 120 minut

**📜 Zasady gry:**
1. 🚫 **Zakaz używania `delay()`!** Każde opóźnienie, mruganie czy odmierzanie czasu musi być zrealizowane za pomocą funkcji `millis()`.
2. 🤝 **Praca w zespole:** Sukces zależy od komunikacji. Zanim zaczniecie pisać kod, musicie ustalić wspólne nazwy zmiennych (tzw. zmienne globalne), przez które Wasze kody będą się komunikować.
3. 🧩 **Piszcie własne funkcje:** Nie wrzucajcie całego kodu do `loop()`. Używajcie mniejszych bloków, aby kod był czytelny.

---

## 🚨 Projekt 1: "Laserowy Sejf" – Wielopoziomowy System Alarmowy

**🎯 Cel:** Stworzenie systemu alarmowego, który uzbraja się i rozbraja za pomocą 3-cyfrowego kodu PIN. Kod wprowadzamy potencjometrem (wybór cyfry) i przyciskiem (zatwierdzenie). Gdy system jest uzbrojony, przecięcie lasera lub ruch (PIR) włącza alarm (piezo + czerwona dioda RGB).

**🧰 Elementy:** Laser, czujnik lasera, PIR, potencjometr, przycisk, dioda RGB, piezo, LCD I2C.

### 📝 1. Wspólne zmienne (Kontrakt między uczniami)
Ustalcie na początku i dodajcie na górze Waszych kodów te same zmienne:
* `int stanSystemu = 0;` *(0 - Rozbrojony, 1 - Wpisywanie PIN, 2 - Uzbrojony, 3 - Alarm)*
* `bool czyWykrytoIntruza = false;`

### 🛠 2. Podział Zadań i Funkcje do napisania

**🧑‍🔧 Uczeń A (Inżynier Sprzętu - Sensory i Alarm)**
*Odpowiadasz za to, co system widzi i jak "krzyczy".*
* `void inicjalizujCzujniki()` – Konfiguracja `pinMode` dla PIR, lasera, diody RGB i piezo.
* `void monitorujOtoczenie()` – Funkcja sprawdzająca stan PIR oraz czujnika lasera. Jeśli wykryje ruch/przerwanie i `stanSystemu == 2`, zmienia `czyWykrytoIntruza = true`.
* `void wlaczAlarm()` – Jeśli `stanSystemu == 3`, funkcja uruchamia pulsujące światło RGB na czerwono oraz przerywany dźwięk piezo. **Użyj `millis()` do pulsowania!** Jeśli stan jest inny, wyłącza diodę i piezo.

**👨‍💻 Uczeń B (Programista Interfejsu - LCD i Logika)**
*Odpowiadasz za to, jak użytkownik obsługuje sejf i za logikę maszyny stanów.*
* `int odczytajPokretlo()` – Odczytuje wartość potencjometru i za pomocą funkcji `map()` zamienia ją na cyfrę od 0 do 9. Zadbaj o to, by cyfry nie "skakały" na ekranie.
* `bool czyWcisnietoPrzycisk()` – Zwraca `true`, gdy przycisk został wciśnięty. Musisz wyeliminować drgania styków (debouncing) przy użyciu `millis()`.
* `void aktualizujEkran()` – Wyświetla komunikaty odpowiednie dla `stanSystemu` (np. "Wprowadz PIN", "UZBROJONY", "ALARM!").
* `void maszynaStanow()` – Główny mózg projektu. Decyduje o przejściach między stanami. Np. jeśli `czyWykrytoIntruza == true`, zmienia `stanSystemu` na 3.

### ⏳ 3. Harmonogram Pracy (120 min)
* **0-10 min:** 🔌 Podłączenie elementów do płytki stykowej. Wspólne ustalenie pinów.
* **10-70 min:** 💻 Praca równoległa. Uczeń A i Uczeń B piszą swoje funkcje w oddzielnych plikach. Testujcie swoje części osobno!
* **70-120 min:** 🔗 Integracja. Łączycie kody w jeden plik, dodajecie funkcje do `setup()` i `loop()`. Testowanie gotowego sejfu.

---

## 🚗 Projekt 2: "Inteligentny Asystent Parkowania" z pilotem IR

**🎯 Cel:** System mierzący odległość (Sonar) i wyświetlający ją jako dynamiczny pasek postępu na ekranie LCD. Dioda RGB płynnie zmienia kolor od zielonego do czerwonego. Pilot IR pozwala wyciszyć dźwięk.

**🧰 Elementy:** Sonar (HC-SR04), LCD I2C, odbiornik IR z pilotem, dioda RGB, piezo.

### 📝 1. Wspólne zmienne (Kontrakt między uczniami)
* `int odlegloscCm = 0;` *(Aktualny pomiar z sonaru)*
* `bool dzwiekWlaczony = true;` *(Sterowane z pilota)*

### 🛠 2. Podział Zadań i Funkcje do napisania

**🧑‍🔧 Uczeń A (Inżynier Pomiarów i Sygnalizacji)**
*Odpowiadasz za płynne mapowanie danych na bodźce wzrokowe i dźwiękowe.*
* `void wykonajPomiar()` – Odczytuje odległość z sonaru. Aktualizuje zmienną `odlegloscCm`. Zrób to tak, by nie blokować całego programu!
* `void aktualizujRGB()` – Bada `odlegloscCm` i używając wyjść PWM (`analogWrite`), płynnie zmienia kolory diody RGB. Im mniejsza odległość, tym więcej czerwonego.
* `void obslugaDzwieku()` – Jeśli `dzwiekWlaczony == true`, funkcja steruje "pikaniem" piezo. Częstotliwość pikania (odstępy czasu między dźwiękami) zależy od odległości. **Użyj `millis()`!**

**👨‍💻 Uczeń B (Programista Interfejsu i Komunikacji IR)**
*Odpowiadasz za pilota i zaawansowaną grafikę na wyświetlaczu.*
* `void zdefiniujZnaki()` – Tworzy własne znaki (*Custom Characters*) dla wyświetlacza LCD (np. pusty kwadrat, połowa kwadratu, pełny kwadrat) i ładuje je do pamięci ekranu w `setup()`.
* `void rysujPasekPostepu()` – Przelicza `odlegloscCm` na liczbę segmentów do wyświetlenia i rysuje płynny pasek na ekranie LCD.
* `void sprawdzPilota()` – Odbiera kody HEX z pilota IR. Jeśli wciśnięto konkretny przycisk (np. "MUTE"), przełącza zmienną `dzwiekWlaczony`.

### ⏳ 3. Harmonogram Pracy (120 min)
* **0-10 min:** 🔌 Ustalenie pinów. Uczeń B pobiera kody ze swojego pilota używając przykładowego szkicu z biblioteki IRremote.
* **10-70 min:** 💻 Praca równoległa. Uczeń A skupia się na płynnym `analogWrite` dla RGB. Uczeń B projektuje piksele do własnych znaków (tablice bajtów).
* **70-120 min:** 🔗 Integracja kodu. Sprawdzenie, czy obsługa pilota nie spowalnia odczytów sonaru.

---

## 🕹️ Projekt 3: Interaktywna Gra Zręcznościowa "Reaktor"

**🎯 Cel:** Stworzenie konsoli, która testuje refleks. Na LCD pojawiają się nagłe komendy (np. "Wychyl joystick GÓRA!", "Zasłoń czujnik!"). Gracz ma mało czasu na wykonanie akcji. Dioda RGB wskazuje "życia" gracza.

**🧰 Elementy:** LCD I2C, joystick, czujnik przeszkód, przycisk, dioda RGB, piezo.

### 📝 1. Wspólne zmienne (Kontrakt między uczniami)
* `int wymaganaAkcja = 0;` *(0-brak, 1-Góra, 2-Dół, 3-Lewo, 4-Prawo, 5-Przycisk, 6-Zasłonienie)*
* `int wykonanaAkcja = 0;` *(Co aktualnie zrobił gracz)*
* `int zycia = 3;`

### 🛠 2. Podział Zadań i Funkcje do napisania

**🧑‍🔧 Uczeń A (Inżynier Kontrolera)**
*Odpowiadasz za to, by gra precyzyjnie reagowała na ruchy gracza, bez błędnych odczytów.*
* `void czytajJoystick()` – Odczytuje wartości analogowe z osi X i Y. Uwzględnij "martwą strefę" na środku, aby uniknąć przypadkowych ruchów. Zmienia `wykonanaAkcja` na 1, 2, 3 lub 4.
* `void czytajSensory()` – Sprawdza stan przycisku (z debouncingiem na `millis()`) oraz czujnika przeszkód. Zmienia `wykonanaAkcja` na 5 lub 6.
* `void zresetujAkcje()` – Ustawia `wykonanaAkcja = 0`, gdy gracz nic nie robi.

**👨‍💻 Uczeń B (Programista Silnika Gry)**
*Odpowiadasz za zasady gry, losowość, upływ czasu i efekty dźwiękowe.*
* `void losujZadanie()` – Ustawia nową `wymaganaAkcja` używając funkcji `random()` i wyświetla komendę na LCD. Zapisuje w zmiennej moment rozpoczęcia zadania.
* `void sprawdzWynik()` – Główna logika. Bada, czy `wymaganaAkcja == wykonanaAkcja`. Jeśli tak, gracz dostaje punkt, a zadanie jest resetowane. Jeśli upłynął określony czas i zadanie nie zostało wykonane, odejmuje `zycia`.
* `void aktualizujStanGry()` – Zarządza diodą RGB (np. 3 życia - zielony, 2 - żółty, 1 - czerwony) i odtwarza krótkie dźwięki na piezo (sukces lub błąd).

### ⏳ 3. Harmonogram Pracy (120 min)
* **0-15 min:** 🔌 Ustalenie pinów. Wspólne "skalibrowanie" joysticka - sprawdzenie w Serial Monitorze wartości.
* **15-75 min:** 💻 Praca równoległa. Uczeń A dopracowuje perfekcyjny odczyt z kontrolerów. Uczeń B tworzy logikę punktacji i czasu w `sprawdzWynik()`.
* **75-120 min:** 🔗 Integracja kodu. Balansowanie poziomu trudności (jak szybko ma upływać czas na odpowiedź, żeby gra była wyzwaniem).
