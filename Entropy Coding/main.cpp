#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>
#include"SymbolVector.h"
#include"BinaryTree.h"
#include"ShannonFanoEncoder.h"
#include"ShannonFanoDecoder.h"
#include"HuffmanEncoder.h"
#include"HuffmanDecoder.h"
using namespace std;

int main()
{
	/* Shannon-Fano */
	/* Since the decoder is derived form the encoder,
	we can use decoder object to do both encoding and
	decoding jobs */
	ShannonFanoDecoder sf_aud, sf_bin, sf_img, sf_txt;
	string sfEncodedFile_aud = "audio_sfEncoded.dat",
		sfEncodedFile_bin = "binary_sfEncoded.dat",
		sfEncodedFile_img = "image_sfEncoded.dat",
		sfEncodedFile_txt = "text_sfEncoded.dat";
	string sfDecodedFile_aud = "audio_sfDecoded.dat",
		sfDecodedFile_bin = "binary_sfDecoded.dat",
		sfDecodedFile_img = "image_sfDecoded.dat",
		sfDecodedFile_txt = "text_sfDecoded.dat";
	string sfCodeTable_aud = "CodeTable_audio_SF.dat",
		sfCodeTable_bin = "CodeTable_bin_SF.dat",
		sfCodeTable_img = "CodeTable_img_SF.dat",
		sfCodeTable_txt = "CodeTable_txt_SF.dat";
	
	/* audio */
	/*sf_aud.loadRawData("audio.dat");
	sf_aud.findUnique();
	cout << "The entropy of the audio file is "
		 << sf_aud.computeEnt() << " bits/symbol." << endl;
	sf_aud.sortSymbolDescend();
	cout << "Symbol list:" << endl;
	sf_aud.listSortedDescend();
	sf_aud.buildSFTree(0, sf_aud.getNumUnique(), 1, 1);
	sf_aud.encodeSF();
	cout << "Code table:" << endl;
	sf_aud.printSFCode();*/
	/*sf_aud.outputSFEncodedFile(sfEncodedFile_aud);
	sf_aud.outputSFCodeTable(sfCodeTable_aud);
	sf_aud.outputSFDecodedFile(sfEncodedFile_aud, sfDecodedFile_aud);*/

	/*sf_bin.loadRawData("binary.dat");
	sf_bin.findUnique();
	cout << "The entropy of the binary file is "
		<< sf_bin.computeEnt() << " bits/symbol." << endl;
	sf_bin.sortSymbolDescend();
	sf_bin.buildSFTree(0, sf_bin.getNumUnique(), 1, 1);
	sf_bin.encodeSF();
	sf_bin.outputSFEncodedFile(sfEncodedFile_bin);
	sf_bin.outputSFDecodedFile(sfEncodedFile_bin, sfDecodedFile_bin);

	sf_img.loadRawData("image.dat");
	sf_img.findUnique();
	cout << "The entropy of the image file is "
		<< sf_img.computeEnt() << " bits/symbol." << endl;
	sf_img.sortSymbolDescend();
	sf_img.buildSFTree(0, sf_img.getNumUnique(), 1, 1);
	sf_img.encodeSF();
	sf_img.outputSFEncodedFile(sfEncodedFile_img);

	sf_txt.loadRawData("text.dat");
	sf_txt.findUnique();
	cout << "There are totally " << sf_txt.getNumTotal() << " characters in the file." << endl;
	cout << "The entropy of the text file is "
		<< sf_txt.computeEnt() << " bits/symbol." << endl;
	sf_txt.sortSymbolDescend();
	cout << "The symbols in frequency descending order:" << endl;
	sf_txt.listSortedDescend();
	cout << "There are totally " << sf_txt.getNumUnique() << " unique characters in the file." << endl;
	sf_txt.buildSFTree(0, sf_txt.getNumUnique(), 1, 1);
	sf_txt.encodeSF();
	cout << "Binary codes:" << endl;
	sf_txt.printSFCode();
	cout << "The avg code length is " << sf_txt.computeAvgLength() << " bits/symbol." << endl;
	sf_txt.outputSFEncodedFile(sfEncodedFile_txt);
	sf_txt.outputSFDecodedFile(sfEncodedFile_txt, sfDecodedFile_txt);*/

	HuffmanDecoder hm_aud, hm_bin, hm_img, hm_txt;
	string hmEncodedFile_aud = "audio_hmEncoded.dat",
		hmEncodedFile_bin = "binary_hmEncoded.dat",
		hmEncodedFile_img = "image_hmEncoded.dat",
		hmEncodedFile_txt = "text_hmEncoded.dat";
	string hmDecodedFile_txt = "text_hmDecoded.dat";

	/* Huffman object */
	hm_aud.loadRawData("audio.dat");
	hm_aud.findUnique();
	cout << "The entropy: " << hm_aud.computeEnt() << endl;
	hm_aud.sortSymbolAscend();
	cout << "Symbol list:" << endl;
	hm_aud.listSortedAscend();
	hm_aud.initialActiveList();
	hm_aud.buildHMTree();
	hm_aud.encodeHM();
	cout << "Code table:" << endl;
	hm_aud.printHMCode();
	//hm_aud.outputHMEncodedFile(hmEncodedFile_aud);

	//hm_bin.loadRawData("binary.dat");
	//hm_bin.findUnique();
	//hm_bin.sortSymbolAscend();
	//hm_bin.initialActiveList();
	//hm_bin.buildHMTree();
	//hm_bin.encodeHM();
	//hm_bin.outputHMEncodedFile(hmEncodedFile_bin);

	//hm_img.loadRawData("image.dat");
	//hm_img.findUnique();
	//hm_img.sortSymbolAscend();
	//hm_img.initialActiveList();
	//hm_img.buildHMTree();
	//hm_img.encodeHM();
	//hm_img.outputHMEncodedFile(hmEncodedFile_img);

	//hm_txt.loadRawData("text.dat");
	//hm_txt.findUnique();
	//hm_txt.sortSymbolAscend();
	//hm_txt.listSortedAscend();
	//hm_txt.initialActiveList();
	//// hm_txt.printActiveList();
	//hm_txt.buildHMTree();
	//hm_txt.encodeHM();
	//cout << "Huffman code:" << endl;
	//hm_txt.printHMCode();
	//cout << "The avg code length is " << hm_txt.computeAvgLength() << " bits/symbol." << endl;
	//hm_txt.outputHMEncodedFile(hmEncodedFile_txt);
	//hm_txt.outputHMDecodedFile(hmEncodedFile_txt, hmDecodedFile_txt);

	return 0;
}

