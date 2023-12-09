import serial
import threading
import tkinter as tk
import time
import pyttsx3

ser = serial.Serial('COM3', 115200, timeout=1)


def while_loop():
    try:
        while True:

            data_received = ser.readline()
            data_received = data_received.replace(b"\r\n", b"")
            # print(f"Received from Arduino: {data_received}")

            if data_received == b"1":
                print("GoOd")
                label.config(text="Authorized Entry!\nDoor will automatically close in 5 seconds", fg="green",
                             font=("", 20, "bold"), bg="black")
                label.place(x=600, y=350)
                root.update()
                pyttsx3.speak("Authorized Card, Please Enter")

                label.config(text="Ready to Read Card !!", fg="white", font=("", 30, "bold"), bg="black")
                label.place(x=600, y=350)
                root.update()

            elif data_received == b"0":
                print("BaD")
                label.config(text="UNAUTHORIZED CARD", fg="red", bg="black",
                             font=("", 30, "bold"))
                root.update()
                pyttsx3.speak("Unauthorized Card, Entry Prohibited")

                label.config(text="Ready to Read Card !!", fg="white", font=("", 30, "bold"), bg="black")
                root.update()

            root.update()

    except KeyboardInterrupt:
        ser.close()
        print("Serial connection closed.")


root = tk.Tk()
root.title("Advanced RFID Door Lock System")
root.geometry("1600x820")
root.config(background="black")

label = tk.Label(text="Ready to Read Card !!", fg="white", font=("", 30, "bold"), bg="black")
label.place(x=600, y=350)


threading.Thread(target=while_loop).start()
root.mainloop()
