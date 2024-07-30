#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Definição da constante M_PI 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Definição da classe LowPassFilter
class LowPassFilter {
public:
    LowPassFilter(float sampleRate, float cutoffFreq) {
        z1 = 0.0f;
        calculateCoefficients(sampleRate, cutoffFreq);
    }

    void calculateCoefficients(float sampleRate, float cutoffFreq) {
        float RC = 1.0f / (2 * M_PI * cutoffFreq);
        float dt = 1.0f / sampleRate;
        alpha = dt / (RC + dt);
    }

    float apply(float sample) {
        float result = alpha * sample + (1 - alpha) * z1;
        z1 = result;
        return result;
    }

private:
    float alpha;
    float z1;
};

// Função para gerar temperatura simulada com ruído
float generateSimulatedTemperature(float time) {
    float amplitude = 5.0f;
    float frequency = 0.1f;
    float baseTemperature = 20.0f;
    float simulatedTemperature = baseTemperature + amplitude * sin(frequency * time);
    
    // Gerar ruído aleatório
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1);
    simulatedTemperature += dis(gen);

    return simulatedTemperature;
}

int main() {
    const float SAMPLE_RATE = 1.0f; // Exemplo: 1 Hz
    const float CUTOFF_FREQ = 0.5f; // Frequência de corte do filtro passa baixa

    LowPassFilter lpFilter(SAMPLE_RATE, CUTOFF_FREQ);

    const int num_samples = 1000;
    std::vector<float> simulatedTemperatures(num_samples);
    std::vector<float> filteredTemperatures(num_samples);

    for (int i = 0; i < num_samples; ++i) {
        float simulatedTemperature = generateSimulatedTemperature(i);
        simulatedTemperatures[i] = simulatedTemperature;
        filteredTemperatures[i] = lpFilter.apply(simulatedTemperature);
        
        // Mensagem de depuração
        std::cout << "Tempo: " << i << ", Simulada: " << simulatedTemperature
                  << ", Filtrada: " << filteredTemperatures[i] << std::endl;
    }

    return 0;
}
