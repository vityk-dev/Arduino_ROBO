// --- USTAWIENIA KALIBRACJI (Zmieniaj tylko tutaj) ---
float korekta_lewy  = 1.0;  // Jeśli skręca w PRAWO, zmniejsz to (np. 0.95)
float korekta_prawy = 1.0;  // Jeśli skręca w LEWO, zmniejsz to (np. 0.95)

//!!! PINY PWM NA ARDUINO NANO: D3, D5, D6, D9, D10, D11 !!!
int L_DIR = 4; // Lewy kierunek (zwykły)
int L_PWM = 5; // Lewy prędkość (PWM ~)
int R_DIR = 8; // Prawy kierunek (zwykły)
int R_PWM = 9; // Prawy prędkość (PWM ~)

void setup() {
  pinMode(L_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(R_PWM, OUTPUT);
}

void loop() {
  // 1. JAZDA DO PRZODU (przez 2 sekundy)
  
  // Lewy silnik
  digitalWrite(L_DIR, LOW); 
  analogWrite(L_PWM, 100 * korekta_lewy); // 150 to bezpieczna prędkość testowa
  
  // Prawy silnik
  digitalWrite(R_DIR, LOW);
  analogWrite(R_PWM, 100 * korekta_prawy);

  delay(2000); // Czas jazdy

  // 2. STOP (przez 2 sekundy - żebyś mógł go złapać/poprawić)
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
  
  delay(2000); // Czas postoju
}
