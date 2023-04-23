#pragma once

class Snapshot {
public:
    Snapshot();
    virtual ~Snapshot() = default;
    bool isCorrect();

protected:
    bool correct;
};
