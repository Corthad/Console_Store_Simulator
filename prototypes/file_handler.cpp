#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct kvector
{
	std::vector<int> keys;
	std::vector<char> values;
};

kvector sorted(std::vector<char>& items, bool reverse = false)
{
	kvector sorted_items;
	for(int i=0; i < items.size(); ++i)
	{
		sorted_items.keys.push_back(i);
		sorted_items.values.push_back(items[i]);
	}

	for(int i=0; i < items.size(); ++i)
	{
		for(int j=0; j < items.size()-1; ++j)
		{
			bool condition = (reverse ? sorted_items.values[j] < sorted_items.values[j+1] : sorted_items.values[j] > sorted_items.values[j+1]);
			if(condition)
			{
				int tmp_key = sorted_items.keys[j];
				char tmp_value = sorted_items.values[j];

				sorted_items.keys[j] = sorted_items.keys[j+1];
				sorted_items.keys[j+1] = tmp_key;

				sorted_items.values[j] = sorted_items.values[j+1];
				sorted_items.values[j+1] = tmp_value;
			}
		}
	}

	return sorted_items;
}

const std::string CHARS = "&-.0123456789<>ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
const int CLEN = CHARS.size();

std::string encode(const std::string& str)
{
	std::string enc_str = str;
	std::vector<char> embeds_count(CLEN);

	for(char c : str)
	{
		int idx = CHARS.find(c);
		embeds_count[idx] += 1;
	}
	kvector sorted_emb = sorted(embeds_count, true);

	std::string embeds(CLEN, '\000');
	for(int i=0; i < sorted_emb.keys.size(); ++i)
	{
		int key = sorted_emb.keys[i];
		embeds[key] = i + 40;
	}

	for(int j=0; j < enc_str.size(); ++j)
	{
		int key = CHARS.find(str[j]);
		enc_str[j] = embeds[key];
	}

	return enc_str + embeds;
}

std::string decode(const std::string& enc_data)
{
    std::string embeds(CLEN, '\000');
	int start_idx = enc_data.size() - CLEN;
	for(int i = 0; i < CLEN; ++i)
	{
		embeds[i] = enc_data[start_idx + i];
	}

	std::cout << embeds << "\n";
	
	std::string dec_str = enc_data;
	for(int j=0; j < enc_data.size(); ++j)
	{
		int pos = embeds.find(enc_data[j]);
		if(pos != std::string::npos)
		{
			dec_str[j] = CHARS[pos];
		}
	}

	return dec_str;
}

int main()
{
	std::string data = "SEED&1010\nDAY&1\nSELLER>MONEY>CASH&12345\nSELLER>MONEY>NON-CASH&12345\nSELLER>ITEMS>PRICES>MILK&120\nSELLER>ITEMS>PRICES>BREAD&80\nSELLER>ITEMS>GTY>MILK&5\nSELLER>ITEMS>QTY>BREAD&10";
	
	std::cout << data << "\n------------------------\n";
	std::string enc_data = encode(data);
	std::cout << enc_data << "\n------------------------\n";
	std::cout << decode(enc_data) << "\n";
}

int load_data(const std::string& path, char mode = 0x00) // Получение данных с объединённых products.txt, seller.txt, buyer.txt
{
    std::ifstream data;
	data.open(path);
	if(!data.is_open())
	{
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
		return 1; // Пустой вектор
	}

	std::string enc_data;
	std::string line;
	while(data >> line)
	{
		enc_data += line;
	}
	std::string dec_data = decode(enc_data);
	std::string word;
	for(char c : dec_data)
	{
		word += c;

		if(word == "SEED")
		{

		}
	}
}

int save_data(const std::string& path)
{

}