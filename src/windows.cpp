#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <windows.h>
#include <commdlg.h>

#include "windows.hpp"
#include "globals.hpp"

std::string Windows::getPathFromUser(std::string name) /// ia path-ul introdus de catre utilizator pentru a salva fisierul
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), name);
    sf::Image icon;
    icon.loadFromFile("assets/images/main_icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Enter path: ");

    pth.setFont(font);
    pth.setFillColor(sf::Color::Green);
    pth.setPosition(200, 0);

    std::string path;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                int key = event.key.code;

                if (key == 58 || key == 36)
                    window.close();

                break;
            }
            if (event.type == sf::Event::TextEntered)
            {
                int ch = event.text.unicode;

                if (ch == 8)
                {
                    if (path.size())
                        path.pop_back();
                }
                else
                    path += ch;

                break;
            }
        }

        pth.setString(path);
        window.clear(sf::Color::White);
        window.draw(text);
        window.draw(pth);
        window.display();
    }

    return path;
}

std::string Windows::getStringFromUser(std::string name) /// citeste cuvantul pe care vrea user-ul sa-l caute
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), name);
    sf::Image icon;
    icon.loadFromFile("assets/images/main_icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Enter keyword: ");

    pth.setFont(font);
    pth.setFillColor(sf::Color::Green);
    pth.setString("");
    pth.setPosition(250, 0);

    std::string path;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                int key = event.key.code;

                if (key == 58 || key == 36)
                {
                    window.close();
                }

                break;
            }
            if (event.type == sf::Event::TextEntered)
            {
                int ch = event.text.unicode;

                if (ch == 8)
                {
                    if (path.size())
                        path.pop_back();
                }
                else
                    path += ch;

                break;
            }
        }

        pth.setString(path);
        window.clear(sf::Color::White);
        window.draw(text);
        window.draw(pth);
        window.display();
    }

    return path;
}

void Windows::throwMessage(std::string message)
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), "");

    sf::Event event;
    sf::Text text;

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(message);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                int key = event.key.code;

                if (key == 58 || key == 36)
                {
                    window.close();
                }

                break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}

std::string Windows::saveAS()
{
    OPENFILENAMEA ofn;
    char szFile[260];      // Buffer for full file path
    char szFileTitle[260]; // Buffer for file title (file name only)

    // Initialize the OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // Handle to the owner window
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';                           // Initialize the file buffer with an empty std::string
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]); // Wide chars
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0';                                     // Initialize file title buffer
    ofn.nMaxFileTitle = sizeof(szFileTitle) / sizeof(szFileTitle[0]); // Wide chars
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";          // Wide character filter
    ofn.nFilterIndex = 1;                                             // Default filter index
    ofn.lpstrInitialDir = NULL;                                       // Initial directory
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;              // Overwrite prompt for save dialog

    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        // File selected and dialog confirmed
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    }
    else
    {
        // Dialog was canceled or an error occurred
        std::cout << "Open file dialog canceled or failed." << std::endl;
        return "";
    }
}

std::string Windows::open()
{
    OPENFILENAMEA ofn;
    char szFile[260];      // Buffer for full file path
    char szFileTitle[260]; // Buffer for file title (file name only)

    // Initialize the OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // Handle to the owner window
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0'; // Initialize the file buffer with an empty std::string
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0'; // Initialize file title buffer
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0"; // ANSI character filter
    ofn.nFilterIndex = 1;                                    // Default filter index
    ofn.lpstrInitialDir = NULL;                              // Initial directory
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box
    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        // File selected and dialog confirmed
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    }
    else
    {
        // Dialog was canceled or an error occurred
        std::cout << "Open file dialog canceled or failed." << std::endl;
        return "";
    }
}

int Windows::saveModal() 
{ ///am invatat de la cei mai buni
    int result = MessageBox(
        NULL,                            
        "Do you want to save changes?",  
        "Save Changes",                  
        MB_YESNOCANCEL | MB_ICONQUESTION 
    );

    return result;
}
