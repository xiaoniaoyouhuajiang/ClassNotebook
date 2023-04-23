#ifndef IREGENERATION_H
#define IREGENERATION_H


class IRegeneration
{
public:
   virtual ~IRegeneration() = default;
   virtual void regeneration() = 0;
};

#endif // IREGENERATION_H
