#include <gmock/gmock.h>
#include <type_traits>
#include <functional>
#include <memory>

namespace v5 {

  // bnfc AST spec
  // (1) Node has one abstract class
  // (1-a) abstract class implements Visitable
  //
  // (2) Node has several implement classes
  // (2-a) implement classes have child elements as field
  // (2-b) implement classes have following methods:
  // * Copy ctor, assign(=)
  // * Constructor with child elements
  // * Dtor
  // * virtual methods of accept, clone
  // * swap

  // -- bnfc sample start
  class Exp;
  class Factor;
  class ImmExp;
  class IdentFactor;
  typedef std::string Ident;

  class Visitor
  {
  public:
    virtual ~Visitor() {}
  };

  class Visitable
  {
  public:
    virtual ~Visitable() {}
    virtual void accept(Visitor *v) = 0;
  };

  // bnfc AST
  class Exp : public Visitable
  {
  public:
    virtual Exp *clone() const = 0;
  };

  class Factor : public Visitable
  {
  public:
    virtual Factor *clone() const = 0;
  };

  class ImmExp : public Exp
  {
  public:
    Factor *factor_;

    ImmExp(const ImmExp & other) { factor_ = other.factor_; }
    ImmExp &operator=(const ImmExp & other) { ImmExp tmp(other);swap(tmp);return *this; }
    ImmExp(Factor *p1) { factor_ = p1; }
    ~ImmExp() {}
    virtual void accept(Visitor *v) {}
    virtual ImmExp *clone() const {}
    void swap(ImmExp & other)  { std::swap(factor_, other.factor_); };
  };

  class IdentFactor : public Factor
  {
  public:
    Ident ident_;

    IdentFactor(const IdentFactor & other) { ident_ = other.ident_; }
    IdentFactor &operator=(const IdentFactor & other) { IdentFactor tmp(other);swap(tmp);return *this; };
    IdentFactor(Ident p1) { ident_ = p1; }
    ~IdentFactor() {}
    virtual void accept(Visitor *v) {}
    virtual IdentFactor *clone() const {};
    void swap(IdentFactor & other) { std::swap(ident_, other.ident_); };
  };
  // bnfc sample end --/


using namespace ::testing;

TEST(FigureTests_v6, simple_instance_and_clone)
{
  auto id = Ident("Hello");
  std::unique_ptr<IdentFactor> factor (new IdentFactor(id));
  std::unique_ptr<ImmExp> exp (new ImmExp(factor.get()));

  //stmt = std::make_unique<Statement>();
  //std::unique_ptr<Prog> p(new Prog());
}

} // v6 namespace
