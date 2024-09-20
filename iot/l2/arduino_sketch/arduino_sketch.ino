void setup() {
    Serial.begin(9600);
}

float result;
int minus;
void loop() {
    if (Serial.available() > 0) {
        int current_byte = Serial.read();
        if (current_byte == '\n') {
            if (minus) {
                result *= -1;
            }

            // y = x^(x^2) * cos(x^2) * sum1..3(2*cos2x)
            float x = result;
            float x_2 = x * x;
            float x_x_2 = pow(x, x_2);
            float cos_x_2 = cos(x * x);
            float sum_1_3 = 2 * cos(2 * x);
            sum_1_3 *= 3;
            result = x_x_2 * cos_x_2 * sum_1_3;

            Serial.println(result);
            result = 0;
            return;
        }
        if (current_byte == '-') {
            minus = 1;
            return;
        }

        current_byte -= 48;
        if (result > 0) {
            result *= 10;
            result += current_byte;
            return;
        }

        result = current_byte;
    }
}
