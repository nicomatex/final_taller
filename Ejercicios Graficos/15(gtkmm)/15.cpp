/*
> Escriba el trozo de código necesario para tildar un Checkbox de una ventana de dialogo.
*/

#include <gtkmm.h>
#include <iostream>

void prompt_checkbox_dialog(){
	Gtk::Dialog dialog;
	Gtk::CheckButton checkbox("Hola");
	dialog.get_action_area()->add(checkbox);
	checkbox.show();
	dialog.run();
}

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc,argv,"ej.taller");
	Gtk::Window ventana;

	ventana.signal_show().connect(std::bind(sigc::ptr_fun(prompt_checkbox_dialog)));
	return app->run(ventana);
}
