/*
 * Copyright 2016- 2018 Koth. All Rights Reserved.
 * =====================================================================================
 * Filename:  seg_backend_api.cc
 * Author:  Koth
 * Create Time: 2016-11-20 20:43:26
 * Description:
 *
 */
#include <string>
#include <thread>
#include <memory>
#include <iostream>
#include <fstream>

#include "base.h"
#include "jsonxx.h"
#include "basic_string_util.h"
#include "tf_seg_model.h"
#include "pos_tagger.h"
#include "third_party/crow/include/crow.h"
#include "tensorflow/core/platform/init_main.h"

DEFINE_int32(port, 9090, "the  api serving binding port");
DEFINE_string(model_path, "kcws/models/seg_model.pbtxt", "the model path");
DEFINE_string(vocab_path, "kcws/models/basic_vocab.txt", "char vocab path");
DEFINE_string(pos_model_path, "kcws/models/pos_model.pbtxt", "the pos tagging model path");
DEFINE_string(word_vocab_path, "kcws/models/word_vocab.txt", "word vocab path");
DEFINE_string(pos_vocab_path, "kcws/models/pos_vocab.txt", "pos vocab path");
DEFINE_int32(max_sentence_len, 80, "max sentence len ");
DEFINE_string(user_dict_path, "", "user dict path");
DEFINE_int32(max_word_num, 50, "max num of word per sentence ");

class SegMiddleware 
{
public:
	struct context {};
	SegMiddleware() {}
	~SegMiddleware() {}
	void before_handle(crow::request& req, crow::response& res, context& ctx) {}
	void after_handle(crow::request& req, crow::response& res, context& ctx) {}
private:
};

int main(int argc, char* argv[]) 
{
	tensorflow::port::InitMain(argv[0], &argc, &argv);
	google::ParseCommandLineFlags(&argc, &argv, true);
	crow::App<SegMiddleware> app;
	kcws::TfSegModel model;
	CHECK(model.LoadModel(FLAGS_model_path,
				FLAGS_vocab_path,
				FLAGS_max_sentence_len,
				FLAGS_user_dict_path)) 
		<< "Load model error";
	
	if (!FLAGS_pos_model_path.empty()) {
		kcws::PosTagger* tagger = new kcws::PosTagger;
		CHECK(tagger->LoadModel(FLAGS_pos_model_path,
					FLAGS_word_vocab_path,
					FLAGS_vocab_path,
					FLAGS_pos_vocab_path,
					FLAGS_max_word_num)) << "load pos model error";
		model.SetPosTagger(tagger);
	}
	std::ifstream in("/home/sunxx/work/test/nlu-ner/train_and_dict/model/origin_corpus/origin_corpus");
	std::string sentence = "";
	//while (std::getline(in, sentence)) {
	while (1) {
		std::cout << "please input query:";
		std::cin >> sentence;
		if (sentence == "q") {
			return 0;
		}

		std::vector<std::string> result;
		std::vector<std::string> tags;
		std::string desc = "";
		//std::cout << "input sentence is:" << sentence << std::endl;
		if (model.Segment(sentence, &result, &tags)) {
			int status = 0;
			//std::cout << "result size:" << result.size() << std::endl;
			//std::cout << "tags size:" << tags.size() << std::endl;
			if (result.size() == tags.size()) {
				int nl = result.size();
				for (int i = 0; i < nl; i++) {
					std::cout << result[i] << "/" << tags[i] << " ";
				}
				std::cout << std::endl;
			} else {
				for (std::string str : result) {
					std::cout << str <<  " ";
				}
				std::cout << std::endl;
			}
			//std::cout << "segments" << std::endl;
		} else {
			desc = "Parse request error";
		}
	
		//std::cout << "status" << std::endl;;
		//std::cout << "msg" << desc << std::endl;
	}
  
	return 0;
}
