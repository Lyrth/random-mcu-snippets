/*
 * A verr simple script to measure pulses. 
 * Specifically measures space between transitions.
 * 
 * Verr simple indeed, lazy enough to not add Hz values.
 */


char state=0;
char laststate=0;
float ct=0;
float lt=0;
float t=0;

void setup()
{
    Serial.begin(9600);

    pinMode(A5, INPUT);
    lt=micros()/1000.0;         
}

void loop()
{
    state=digitalRead(A5);
    
    if (state!=laststate)
    {
        laststate=state;
        ct=micros()/1000.0;
        
        t = ct - lt;

        Serial.print("t = ");
        Serial.print(t);
        Serial.println(" mS");
       
        lt=ct;
    }


}

