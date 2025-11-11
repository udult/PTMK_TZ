// Converting data.csv into dataset.txt with [Ivanov Ivan Ivanovich, male] format
// dataset is taken from https://www.kaggle.com/datasets/rai220/russian-cyrillic-names-and-sex?resource=download
// debug output is provided

#include <cctype>
#include <locale>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main()
{
	std::unordered_map<wchar_t, std::string> translit_map = {
		{L'А', "a" }, {L'Б', "b"   }, {L'В', "v" }, {L'Г', "g" }, {L'Д', "d" },
		{L'Е', "e" }, {L'Ё', "yo"  }, {L'Ж', "zh"}, {L'З', "z" }, {L'И', "i" },
		{L'Й', "y" }, {L'К', "k"   }, {L'Л', "l" }, {L'М', "m" }, {L'Н', "n" },
		{L'О', "o" }, {L'П', "p"   }, {L'Р', "r" }, {L'С', "s" }, {L'Т', "t" },
		{L'У', "u" }, {L'Ф', "f"   }, {L'Х', "kh"}, {L'Ц', "ts"}, {L'Ч', "ch"},
		{L'Ш', "sh"}, {L'Щ', "shch"}, {L'Ъ', ""  }, {L'Ы', "y" }, {L'Ь', ""  },
		{L'Э', "e" }, {L'Ю', "yu"  }, {L'Я', "ya"}, { ',', " " }
	};

	std::wifstream input_file("../data/data.csv");
	if (!input_file.is_open())
	{
		std::cerr << "cannot open input file" << std::endl;
		return 1;
	}

	std::ofstream output_file("../data/dataset.txt");
	if (!output_file.is_open())
	{
		std::cerr << "cannot open output file" << std::endl;
		return 1;
	}

	/* setting russian locale for programm */
	std::locale::global(std::locale("ru_RU.UTF-8"));

	/* setting russian locale for input file */
    input_file.imbue(std::locale());
  
  	std::string line;
	std::wstring wline;

	for (int i = 0; i < 1240467 * 2 && std::getline(input_file, wline); i++)
	{
		if (i < 1240467)
			continue;
		
		// save new string in ascii latin format
		for (wchar_t ch : wline) line += translit_map[ch];

		// name starts with upper letter
		line[0] = std::toupper(line[0]);

		for (size_t j = 1; j < line.size(); j++)
			if (line[j - 1] == ' ') line[j] = std::toupper(line[j]);

		// finding num of pos to substitute gender
		size_t delpos = line.find_last_of(' ');

		if (delpos == std::string::npos)
		{
			std::cerr << "no delpos on iter " << i << std::endl;
			return 1;
		}

		// substitute gender
		if (line.substr(delpos + 1) == "M")
		{
			line.erase(delpos);
			line += ",male";
		}

		else
		{
			line.erase(delpos);
			line += ",female";
		}

		// debug output
		std::cout << i << " " << line << std::endl;
		
		// file output
		output_file << line << std::endl;
		
		line.clear();
		wline.clear();
	}

	input_file.close();
	output_file.close();

	return 0;
}

/* */