#pragma once // Если это отдельный .h файл

#include <iostream>

// --- Подключаем заголовки для нужной ОС ---

#ifdef _WIN32
    // Windows
    #include <windows.h>
    #include <psapi.h> // Для GetProcessMemoryInfo
    // Примечание: В Windows вам может потребоваться
    // в настройках компоновщика добавить Psapi.lib

#elif __linux__
    // Linux
    #include <fstream>
    #include <string>
    #include <sstream>

#elif __APPLE__
    // macOS
    #include <mach/mach.h>

#else
    #warning "Платформа не поддерживается для отслеживания памяти."
#endif


/**
 * @brief Возвращает ТЕКУЩEE потребление физической памяти (RSS) процессом.
 * @return Память в байтах или 0, если ОС не поддерживается.
 */
size_t getCurrentRSS() {
#ifdef _WIN32
    // --- Реализация для Windows ---
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize; // Текущий RSS
    }
    return 0;

#elif __linux__
    // --- Реализация для Linux ---
    // Читаем /proc/self/status, ищем "VmRSS:"
    std::ifstream statusFile("/proc/self/status");
    std::string line;
    while (std::getline(statusFile, line)) {
        if (line.rfind("VmRSS:", 0) == 0) { // Проверяем, что строка начинается с VmRSS:
            std::istringstream iss(line.substr(6)); // Пропускаем "VmRSS:"
            long rss_kb;
            iss >> rss_kb; // Значение там в КИЛОбайтах
            return static_cast<size_t>(rss_kb * 1024); // Конвертируем в байты
        }
    }
    return 0;

#elif __APPLE__
    // --- Реализация для macOS ---
    mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &infoCount) != KERN_SUCCESS) {
        return 0;
    }
    return info.resident_size; // Текущий RSS в байтах

#else
    // --- Неподдерживаемая ОС ---
    return 0;
#endif
}

/**
 * @brief Возвращает ПИКОВОЕ потребление физической памяти (RSS) процессом.
 * @return Память в байтах или 0, если ОС не поддерживается.
 */
size_t getPeakRSS() {
#ifdef _WIN32
    // --- Реализация для Windows ---
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.PeakWorkingSetSize/1024; // Пиковый RSS
    }
    return 0;

#elif __linux__
    // --- Реализация для Linux ---
    // Читаем /proc/self/status, ищем "VmHWM:" (High Water Mark)
    std::ifstream statusFile("/proc/self/status");
    std::string line;
    while (std::getline(statusFile, line)) {
        if (line.rfind("VmHWM:", 0) == 0) {
            std::istringstream iss(line.substr(6)); // Пропускаем "VmHWM:"
            long rss_kb;
            iss >> rss_kb; // Значение в КИЛОбайтах
            return static_cast<size_t>(rss_kb * 1024); // Конвертируем в байты
        }
    }
    return 0;

#elif __APPLE__
    // --- Реализация для macOS ---
    mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &infoCount) != KERN_SUCCESS) {
        return 0;
    }
    return info.resident_size_max; // Пиковый RSS в байтах

#else
    // --- Неподдерживаемая ОС ---
    return 0;
#endif
}