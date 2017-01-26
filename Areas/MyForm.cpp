#include "MyForm.h"
#include "areacodes.h"

using namespace One;

void Main(array<String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyForm);
}
