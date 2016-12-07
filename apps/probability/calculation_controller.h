#ifndef PROBABILITY_CALCULATION_CONTROLLER_H
#define PROBABILITY_CALCULATION_CONTROLLER_H

#include <escher.h>
#include "law.h"
#include "law_curve_view.h"
#include "image_table_view.h"

namespace Probability {

class CalculationController : public ViewController {
public:
  CalculationController(Responder * parentResponder, Law * law);
  View * view() override;
  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  Law * law();
  int highlightedSubviewIndex() const;
  void selectSubview(int subviewIndex);
private:
  class ContentView : public View {
  public:
    ContentView(Responder * parentResponder, Law * law);
    void layoutSubviews() override;
    void drawRect(KDContext * ctx, KDRect rect) const override;
    LawCurveView * lawCurveView();
    ImageTableView * imageTableView();
    EditableTextCell * calculationCellAtIndex(int index);
    constexpr static int k_maxNumberOfEditableFields = 3;
  private:
    constexpr static KDCoordinate k_textFieldWidth = 35;
    constexpr static KDCoordinate k_charWidth = 7;
    constexpr static KDCoordinate k_textMargin = 5;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    LawCurveView m_lawCurveView;
    ImageTableView m_imageTableView;
    PointerTextView m_text[k_maxNumberOfEditableFields];
    EditableTextCell m_calculationCell[k_maxNumberOfEditableFields];
    Law * m_law;
  };
  ContentView m_contentView;
  int m_highlightedSubviewIndex;
  Law * m_law;
};

}

#endif
