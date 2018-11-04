#ifndef PCA9685_H
#define PCA9685_H

#define PCA9685_PINS 16

class pca9685 {
private:
	#ifndef PCA9685_DUMMY
		int FFileDescriptor;
	#endif
    int select_register(int channel);
    public:
    pca9685 (int address);
    ~pca9685();
    void alloff();
    void write_i2c(int ic_register, int value);
    void set_intensity(int channel, int intensity);
    void set_frequency(double frequency);
};

#endif //PCA9685_H
