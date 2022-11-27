#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;

int main() try
{
    vector<string> devices = sf::SoundBufferRecorder::getAvailableDevices();
    string defaultDevice = sf::SoundBufferRecorder::getDefaultDevice();

    cout << "Default Device: \n\t" << defaultDevice << endl;
    cout << "Available Devices: \n";

    int i = 1, def = 1;
    for (auto device : devices)
    {
        if(device == defaultDevice) def = i;
        cout << "\t" << i++ << ": " << device << endl;
    }

    cout << "Select Device #: ";
    int id = 1;
    cin >> id;
    if (id>devices.size()) id = def;
    id --;
    cout << "Set device: " << devices[id] << endl;

    cout << "Set Sample Rate (4000 ~ 192000, 44100 is CD quality): ";
    int rate = 44100;
    cin >> rate;
    if (rate<4000) rate = 4000;
    cout << "Set sample rate: " << rate << endl;

    // Ready to start recording
    std::cout << "Press enter to start recording audio ..." << endl;
    cin.ignore(10000, '\n');

    sf::SoundBufferRecorder recorder;
    recorder.setDevice(devices[id]);

    recorder.start(rate);
    cout << "Recording... \n" << "Press Enter to Stop" << endl;
    cin.ignore(10000, '\n');
    recorder.stop();

    sf::SoundBuffer buffer = recorder.getBuffer();

    cout << "Sound Infomation:" << endl
         << "\t" << buffer.getDuration().asSeconds() << " seconds" << endl
         << "\t" << buffer.getSampleRate() << " samples/seconds" << endl
         << "\t" << buffer.getChannelCount() << " channels" << endl
         ;

    // Save sound buffer to a file
    string file = "record.flac";
    cout << "Choose the file name to create, " << file << " eg." << endl;
    cout << "The supported audio formats are: WAV, OGG/Vorbis, FLAC." << endl;
    std::getline(cin, file);
    buffer.saveToFile(file);

    // Create a sound instance and play it
    sf::Sound sound(buffer);
    sound.play();

    // Wait until play finished
    while (sound.getStatus() == sf::Sound::Playing)
    {
        float pos = sound.getPlayingOffset().asSeconds();
        cout << "\rPlaying ... " << pos << " sec." << endl << std::flush;

        // Leave some CPU time for other threads
        sf::sleep(sf::milliseconds(100));
    }
}
catch (const char * er)
{
    cout << "Error: " << er << endl;
}