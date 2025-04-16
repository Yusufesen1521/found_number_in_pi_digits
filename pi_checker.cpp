#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <chrono>
#include <iomanip>

// Callback function to write received data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchPiDigits(CURL* curl, int start, int length) {
    std::string url = "https://api.pi.delivery/v1/pi?start=" + std::to_string(start) + "&numberOfDigits=" + std::to_string(length);
    std::string response;
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error: Failed to fetch pi digits: " << curl_easy_strerror(res) << std::endl;
        return "";
    }
    
    size_t content_pos = response.find("\"content\":\"");
    if (content_pos == std::string::npos) {
        std::cerr << "Error: Invalid response format" << std::endl;
        return "";
    }
    
    content_pos += 11; // Skip over "content":"
    size_t end_pos = response.find("\"", content_pos);
    return response.substr(content_pos, end_pos - content_pos);
}

int main() {
    // Read the number to search from check.txt
    std::ifstream check_file("check.txt");
    if (!check_file.is_open()) {
        std::cerr << "Error: Could not open check.txt" << std::endl;
        return 1;
    }
    
    std::string search_number;
    std::getline(check_file, search_number);
    check_file.close();
    
    // Initialize CURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: CURL initialization failed" << std::endl;
        return 1;
    }
    
    const int CHUNK_SIZE = 1000;
    const int MAX_DIGITS = 1000000;
    bool found = false;
    int current_position = 0;
    
    std::cout << "Searching for: " << search_number << std::endl;
    
    // Start timing
    auto start_time = std::chrono::high_resolution_clock::now();
    
    while (current_position < MAX_DIGITS && !found) {
        std::cout << "Checking digits " << current_position << " to " << (current_position + CHUNK_SIZE - 1) << "...\r" << std::flush;
        
        std::string pi_digits = fetchPiDigits(curl, current_position, CHUNK_SIZE);
        if (pi_digits.empty()) {
            break;
        }
        
        size_t found_pos = pi_digits.find(search_number);
        if (found_pos != std::string::npos) {
            found = true;
            // Calculate elapsed time
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            std::cout << "\nNumber found at position: " << (current_position + found_pos) << std::endl;
            std::cout << "Search took: " << std::fixed << std::setprecision(2) 
                      << (duration.count() / 1000.0) << " seconds" << std::endl;
            break;
        }
        
        // Move to next chunk, but overlap by the length of search_number - 1
        current_position += (CHUNK_SIZE - (search_number.length() - 1));
    }
    
    if (!found) {
        // Calculate elapsed time for unsuccessful search
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        
        std::cout << "\nNumber not found in the first million digits of pi" << std::endl;
        std::cout << "Search took: " << std::fixed << std::setprecision(2) 
                  << (duration.count() / 1000.0) << " seconds" << std::endl;
    }
    
    curl_easy_cleanup(curl);
    return 0;
} 