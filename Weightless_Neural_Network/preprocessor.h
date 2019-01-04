#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
//TODO: Include opencv classes and implement the Binary and Gray classes

class Preprocessor{
public:
    virtual Preprocessor();
    virtual Mat preprocess(const Mat&);
};

class Binary: public Preprocessor{
public:
    Mat preprocess(const Mat& source);
};

class Grey: public Preprocessor{

public:
    Mat preprocess(const Mat& source);
}

#endif // PREPROCESSOR_H
