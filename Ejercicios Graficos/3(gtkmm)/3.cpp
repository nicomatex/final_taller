/*
> Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo.
*/

#include <gtkmm.h>
#include <iostream>


#define TXT_WIDTH 200
#define TXT_HEIGHT 30
#define BTN_WIDTH 200
#define BTN_HEIGHT 30

void hide_textbox(Gtk::Entry &textbox){
	std::string texto = textbox.get_text();
	std::cout << texto << std::endl;
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "ejercicio.taller");
    Gtk::Window window;
    Gtk::Fixed contenedor;
    window.add(contenedor);

    Gtk::Entry textbox;
	textbox.set_size_request(TXT_WIDTH,TXT_HEIGHT);
    contenedor.put(textbox,0,0);
    
    Gtk::Button boton("Boton");
	boton.set_size_request(BTN_WIDTH,BTN_HEIGHT);
    contenedor.put(boton,0,TXT_HEIGHT);

    contenedor.show();
    textbox.show();
    boton.show();

    boton.signal_clicked().connect(std::bind(sigc::ptr_fun(hide_textbox),std::ref(textbox)));

    return app->run(window);
}
