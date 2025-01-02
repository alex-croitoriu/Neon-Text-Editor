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
    icon.loadFromFile("assets/images/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;

    text.setFont(globalFont);
    text.setFillColor(sf::Color::Black);
    text.setString("Enter path: ");

    pth.setFont(globalFont);
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
    icon.loadFromFile("assets/images/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;

    text.setFont(globalFont);
    text.setFillColor(sf::Color::Black);
    text.setString("Enter keyword: ");

    pth.setFont(globalFont);
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
               // std::cerr << key << '\n';
                if (key == 58 || key == 36)
                {
                    window.close();
                }

                break;
            }
            if (event.type == sf::Event::TextEntered)
            {
                int ch = event.text.unicode;
                std::cerr << ch << '\n';

                if (ch == 6 || ch == 18 || ch == 7)
                    break;

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

    text.setFont(globalFont);
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
    char szFile[260];
    char szFileTitle[260];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0';
    ofn.nMaxFileTitle = sizeof(szFileTitle) / sizeof(szFileTitle[0]);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    }
    else
    {
        std::cout << "Open file dialog canceled or failed." << std::endl;
        return "";
    }
}

std::string Windows::open()
{
    OPENFILENAMEA ofn;
    char szFile[260];
    char szFileTitle[260];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0';
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    }
    else
    {
        std::cout << "Open file dialog canceled or failed." << std::endl;
        return "";
    }
}

int Windows::saveModal()
{
    int result = MessageBox
    (
        NULL,
        L"Do you want to save changes?",
        L"Save Changes",
        MB_YESNOCANCEL | MB_ICONQUESTION
    );

    return result;
}
