#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

#include <tensorflow/c/c_api.h>
#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>

#include "tfmodel.h"

namespace tf {

class TfModel;
}  // namespace tf

//get tensorflow version for c library
int test_version();

//test create session
int test_create_session();

//test load cnn tensorflow model
int test_load_cnn_classifier_model();

//test load bi lstm crf model
int test_load_bi_lstm_crf_model();

int main() 
{
    test_version();
    
    test_create_session();
    
    test_load_cnn_classifier_model();

    test_load_bi_lstm_crf_model();

    return 0;
}

int test_create_session()
{
    tensorflow::Session* session;
    tensorflow::Status status = tensorflow::NewSession(tensorflow::SessionOptions(), &session);
    
    if (!status.ok()) {
        std::cout << status.ToString() << std::endl;
        return 1;
    }
    
    std::cout << "Session successfully created." << std::endl;

    return 0;
}

int test_version() 
{
    std::cout << "Hello from TensorFlow C library version" << TF_Version() << std::endl;

    return 0;
}

int test_load_cnn_classifier_model()
{
    std::unique_ptr<tf::TfModel> model_;
	
    model_.reset(new tf::TfModel());
    
    std::string model_path = "./kcws/models/cnn_model.pbtxt";
	if (!model_->Load(model_path)) {
		std::cout << "Could not load model from: " << model_path << std::endl;
		return false;
	}

    //create input tensor
	std::vector<tensorflow::Tensor> trans_tensors;
    
    //test load other tensorflow model
    std::vector<std::string> output_names({"score/my_output"});
    
    std::vector<std::pair<std::string, tensorflow::Tensor> > inputTensors;

    //intput x tensor
    std::vector<int> x = {346, 246, 28, 2795, 777, 83, 102, 533, 1100, 18, 584, 410, 1049, 884, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ndim = x.size();
    tensorflow::Tensor input_x(tensorflow::DT_INT32, tensorflow::TensorShape({1, 30}));
    auto x_map = input_x.tensor<int, 2>();
    for (int j = 0; j < ndim; j++) {
        x_map(0, j) = x[j];
    }
    inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("input_x", input_x)); 
    
    //input keep_prob
    tensorflow::Tensor keep_prob(tensorflow::DT_FLOAT, tensorflow::TensorShape({1}));
    keep_prob.vec<float>()(0) = 1.0f;
    inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("keep_prob", keep_prob));

	if (!model_->Eval(inputTensors, output_names, trans_tensors)) {
		std::cout << "Error during get trans tensors: " << std::endl;
		return false;
	}

    //get output res
    std::cout<< "Reading from layer " << output_names[0] << std::endl;
	tensorflow::Tensor* output = &trans_tensors[0];
	const Eigen::TensorMap<Eigen::Tensor<float, 1, Eigen::RowMajor>,
		  Eigen::Aligned>& prediction = output->flat<float>();
	const int count = prediction.size();

    //test cout result tensor
    for (int i = 0; i < count; ++i) {
        const float value = prediction(i);
        std::cout << i << ":" << value << std::endl;
        // value是该张量以一维数组表示时在索引i处的值。
    }

	return 0;
}

int test_load_bi_lstm_crf_model()
{
    std::unique_ptr<tf::TfModel> model_;
	
    model_.reset(new tf::TfModel());
    
    std::string model_path = "./kcws/models/alerts_biLSTM_crf.pb";
	if (!model_->Load(model_path)) {
		std::cout << "Could not load model from: " << model_path << std::endl;
		return false;
	}

    //create input tensor
	std::vector<tensorflow::Tensor> trans_tensors;
    
    //test load other tensorflow model
    std::vector<std::string> output_names({"decode_tags"});
    
    std::vector<std::pair<std::string, tensorflow::Tensor> > inputTensors;

    //intput word_ids tensor
    std::initializer_list<int> v_a = {17, 48, 211, 404, 2170, 2560, 4, 3141, 682};
    tensorflow::Tensor tensor_in_a(tensorflow::DT_INT32, tensorflow::TensorShape({1, 9}));
    tensor_in_a.matrix<int>().setValues({v_a});
    inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("word_ids", tensor_in_a)); 
    //std::vector<int> x = {17, 48, 211, 404, 2170, 2560, 4, 3141, 682};
    //int ndim = x.size();
    //tensorflow::Tensor input_x(tensorflow::DT_INT32, tensorflow::TensorShape({1, 9}));
    //auto x_map = input_x.tensor<int, 2>();
    //for (int j = 0; j < ndim; j++) {
    //    x_map(0, j) = x[j];
    //}
    //inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("word_ids", input_x)); 
    
    //input dropout
    tensorflow::Tensor dropout(tensorflow::DT_FLOAT, tensorflow::TensorShape({1}));
    dropout.vec<float>()(0) = 1.0f;
    inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("dropout", dropout));

    //input sequence_lengths
    tensorflow::Tensor sequence_lengths(tensorflow::DT_INT32, tensorflow::TensorShape({1}));
    sequence_lengths.vec<int>()(0) = 9;
    inputTensors.push_back(std::pair<std::string, tensorflow::Tensor>("sequence_lengths", sequence_lengths));

	if (!model_->Eval(inputTensors, output_names, trans_tensors)) {
		std::cout << "Error during get trans tensors: " << std::endl;
		return false;
	}

    //get output res
    std::cout<< "Reading from layer:" << output_names[0] << std::endl;
	tensorflow::Tensor* output = &trans_tensors[0];
	const Eigen::TensorMap<Eigen::Tensor<int, 1, Eigen::RowMajor>, Eigen::Aligned>& prediction = output->flat<int>();
	const int count = prediction.size();

    //test cout result tensor
    for (int i = 0; i < count; ++i) {
        const int value = prediction(i);
        std::cout << i << ":" << value << std::endl;
        // value是该张量以一维数组表示时在索引i处的值。
    }

	return 0;
}

// Hello from TensorFlow C library version1.11.0-rc1
