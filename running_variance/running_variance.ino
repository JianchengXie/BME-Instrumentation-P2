// initialize input port
int eyebrowPin = A0; // from eyebrow
int cheekPin = A3; // from cheek

int eyebrow_min = 10000;
int cheek_min = 10000;

int window_size = 10; // window width for running average
int eyebrows[10];
int cheeks[10];

int variance(int a[], int n) 
{   
    // Compute mean (average of elements) 
    int sum = 0; 
    
    for (int i = 0; i < n; i++) sum += a[i];    
    int mean = (int)sum / (int)n; 
    // Compute sum squared differences with mean. 
    int sqDiff = 0; 
    for (int i = 0; i < n; i++) 
        sqDiff += (a[i] - mean) * (a[i] - mean); 
    return (int)sqDiff / n; 
} 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Serial1.begin(9600);
}

void loop() {
  for (int i = 0; i < window_size; i++) {
    analogRead(eyebrowPin);
    delay(10);
    eyebrows[i] = analogRead(eyebrowPin);
    delay(1);
    analogRead(cheekPin);
    delay(10);
    cheeks[i] = analogRead(cheekPin);
    delay(1);
  }
  // //eyebrow = eyebrow / window;
  // if (eyebrow < eyebrow_min && eyebrow > 50) {
  //   eyebrow_min = eyebrow;
  // }
  // eyebrow -= eyebrow_min;
  // //cheek = cheek / window;
  // if (cheek < cheek_min && cheek > 50) {
  //   cheek_min = cheek;
  // }
  // cheek -= cheek_min;
  Serial.print(variance(eyebrows, window_size));
  Serial.print(" ");
  Serial.print(variance(cheeks, window_size));
  Serial.println();
}


