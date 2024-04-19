void BuzzerOff(int pin){
	digitalWrite(pin, HIGH);
}
void BuzzerOn(int pin){
	digitalWrite(pin, LOW);
}
void BuzzerRing(int buzzerPin){
	BuzzerOn(buzzerPin);
	delay(100);
	BuzzerOff(buzzerPin);
	delay(1);
}
