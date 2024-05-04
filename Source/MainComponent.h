#pragma once

#include <JuceHeader.h>
#include "boundHelper.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
enum ColorIndex{
    fillColour = 0,
    BackgroundColour1,
    BackgroundColour2,
    BackgroundColour3,
    BackgroundColour4,
    NUMCOLORS
};

enum gradientModes{
    NoGradient = 0,
    RadialGradient,
    TriRadial,
    QuadRadial,
    NUMGRADIENTS
};

struct designerValues{
    
    designerValues()
       {
        colours.push_back(juce::Colours::white);
        colours.push_back(juce::Colours::white);
        colours.push_back(juce::Colours::white);
        colours.push_back(juce::Colours::white);
        colours.push_back(juce::Colours::white);
       }
    
    juce::String projectName;
    int colorIndex = 0;
    std::vector<juce::Colour> colours;
    
    int gradientMode = 0; // none, radial, horizontal
    float gradientPositionsX[5];
    float gradientPositionsY[5];
    
    bool colorChange = false;
    juce::Colour* getCurrentColor(){
        return &colours[colorIndex];
    }
};


class ControlWindow final : public juce::DocumentWindow,
private juce::ChangeListener
{
public:
    ControlWindow (const juce::String& name, designerValues& dV, int buttonsNeeded, int width, int height) :
        juce::DocumentWindow (name, juce::Colours::white, buttonsNeeded), designer(dV)
    {
        juce::Rectangle<int> bounds{0,0,width,height};
        
        contentComponent.reset(new Component());
        contentComponent->setBounds(0,0,width,height);
        setContentOwned(contentComponent.get(), true);
        int currentY = 0;
        int rowOff = 5;
        int controlHeight = 30;
        contentComponent->addAndMakeVisible(&projectName);
        int widthHalf = width * 0.5f;
        // project name
        projectName.setBounds(widthHalf,currentY,200,controlHeight);
        projectName.setText(designer.projectName);
        projectName.setJustification(juce::Justification::centred);
        projectName.onTextChange = [this]{
            designer.projectName = projectName.getText();
            updateContolColours();
        };
        int width4 = width * 0.25f;
        //gradients
        contentComponent->addAndMakeVisible(&gradients);
        gradients.setBounds(0,currentY,width4,controlHeight);
        gradients.addItem("None", 1);
        gradients.addItem("Radial", 2);
        gradients.addItem("Tri-Radial", 3);
        gradients.addItem("Quad-Radial", 4);
        
        gradients.onChange = [this]{
            designer.gradientMode = gradients.getSelectedId() - 1;
            updateContolColours();
        };
        int throughX = width4;
        juce::String names[5]{"Fill","1","2","3","4"};
        int colorIndexOffset = 0;
        for(int i = 0; i < 5; i++){
            colorIndexOffset++;
            if(i == 1){
                currentY += controlHeight + rowOff;
                throughX = 0;
            }
            contentComponent->addAndMakeVisible(&backgroundColorButtons[i]);
            backgroundColorButtons[i].setBounds(throughX,currentY,width4,controlHeight);
            backgroundColorButtons[i].setButtonText(names[i]);
            backgroundColorButtons[i].onClick = [this,i]{
                designer.colorIndex = i;
                updateContolColours();
            };
            throughX += width4;
        }
        currentY += controlHeight + rowOff;
        
   
        throughX = 0;
        float valuesX[5] = {0.0f,1.0f,1.0f,0.0f};
        float valuesY[5] = {0.0f,0.0f,1.0f,1.0f};
        for(int i = 0; i < 5; i++){
            contentComponent->addAndMakeVisible(&gradientControlsX[i]);
            gradientControlsX[i].setBounds(throughX,currentY,width4,controlHeight);
            gradientControlsX[i].setRange(-2.0, 2.0);
            gradientControlsX[i].setValue(valuesX[i]);
            gradientControlsX[i].setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
            gradientControlsX[i].setTextBoxStyle(juce::Slider::TextBoxRight, false, width4 * 0.4f, controlHeight);
            gradientControlsX[i].setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
            gradientControlsX[i].onValueChange = [this,i]{
                designer.gradientPositionsX[i] = gradientControlsX[i].getValue();
                updateContolColours();
            };
            
            contentComponent->addAndMakeVisible(&gradientControlsY[i]);
            gradientControlsY[i].setBounds(throughX,currentY + controlHeight,width4,controlHeight);
            gradientControlsY[i].setRange(-2.0, 2.0);
            gradientControlsY[i].setValue(valuesY[i]);
            gradientControlsY[i].setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
            gradientControlsY[i].setTextBoxStyle(juce::Slider::TextBoxRight, false, width4 * 0.4f, controlHeight);
            gradientControlsY[i].setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
            gradientControlsY[i].onValueChange = [this,i]{
                designer.gradientPositionsY[i] = gradientControlsY[i].getValue();
                updateContolColours();
            };
            throughX += width4;
        }
        
        currentY += controlHeight + rowOff + controlHeight;
        // x Y of gradients
        
        
    }

    ~ControlWindow()
    {
        contentComponent = nullptr;
       // selector.removeChangeListener (this);
    }

    void closeButtonPressed()
    {
        delete this;
    }
    
    void updateContolColours(){
        
        for(int i = 0; i < 5; i++){
            backgroundColorButtons[i].setColour(juce::TextButton::buttonColourId, designer.colours[i]);
            if(i >= 1){
                gradientControlsX[i-1].setColour(juce::Slider::thumbColourId, designer.colours[i]);
                gradientControlsY[i-1].setColour(juce::Slider::thumbColourId, designer.colours[i]);
            }
        }
    }
    
 
private:
    designerValues& designer;
    std::unique_ptr<juce::Component> contentComponent;

    void changeListenerCallback (juce::ChangeBroadcaster* source)
    {
//        if (source == &selector){
//            backgroundColour = selector.getCurrentColour();
//            setBackgroundColour (backgroundColour);
//        }
    }

    juce::TextEditor projectName;
    juce::ComboBox gradients;
    juce::Slider gradientControlsX[5];
    juce::Slider gradientControlsY[5];
    juce::TextButton backgroundColorButtons[5];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlWindow)
};



 class ColourSelectorWindow final : public juce::DocumentWindow,
private juce::ChangeListener
 {
 public:
     ColourSelectorWindow (const juce::String& name, designerValues& dV, int buttonsNeeded, int width, int height) : designer(dV),
         juce::DocumentWindow (name, juce::Colours::black, buttonsNeeded)
     {
   
         
         // Set up the content component
                contentComponent.reset(new Component());
         contentComponent->setBounds(0,0,width,height);
                setContentOwned(contentComponent.get(), true);
         setBackgroundColour (juce::Colours::black);
         int colorHeight = height * 0.5f;
         selector.setCurrentColour (selectionColour);
         selector.setColour (juce::ColourSelector::backgroundColourId, juce::Colours::transparentWhite);
         selector.addChangeListener (this);
         selector.setBounds(0,0,width,colorHeight);
         contentComponent->addAndMakeVisible(&selector);
        // setContentOwned (&selector, false);
//
                // Create a button
         
         juce::Rectangle<int> lowerBounds{0,colorHeight,width,(int)(colorHeight)};
         int width3 = width * 0.3333333f;
         int buttonWidth = width3 * 0.8f;
         int buttonHeight = 30;
         int yOff = buttonHeight * 0.2f;
         for(int i = 0; i < 18; i++){
             button[i].reset(new juce::TextButton(""));
             button[i]->setBounds(position::getCenter(position::getPositionInRectLinear(lowerBounds, i, 10, 3),buttonWidth, buttonHeight));
             contentComponent->addAndMakeVisible(button[i].get());
             button[i]->onClick = [this, i]{
                 if(swatch){
                     selectionColour = button[i]->findColour(juce::TextButton::buttonColourId);
                     selector.setCurrentColour (selectionColour);
                     setColours();
                 }else{
                     auto cc = designer.getCurrentColor();
                     *cc = button[i]->findColour(juce::TextButton::buttonColourId);
                 }
             };
         }
        
         darkbutton[0].reset(new juce::TextButton(""));
         darkbutton[0]->setBounds(button[15]->getX(),button[15]->getY()+buttonHeight + yOff, buttonWidth, buttonHeight);
         contentComponent->addAndMakeVisible(darkbutton[0].get());
         darkbutton[0]->onClick = [this]{
             if(swatch){
                 selectionColour = getRandomColour();
                 selector.setCurrentColour (selectionColour);
                 setColours();
             }else{
                 auto cc = designer.getCurrentColor();
                 *cc = darkbutton[0]->findColour(juce::TextButton::buttonColourId);
             }
         };
         darkbutton[0]->setColour(juce::TextButton::buttonColourId, juce::Colours::white);
         
         darkbutton[1].reset(new juce::TextButton(""));
         darkbutton[1]->setBounds(button[16]->getX(),button[16]->getY()+buttonHeight + yOff, buttonWidth, buttonHeight);
         contentComponent->addAndMakeVisible(darkbutton[1].get());
         darkbutton[1]->onClick = [this]{
             if(swatch){
                 selectionColour = getRandomColour();
                 selector.setCurrentColour (selectionColour);
                 setColours();
             }else{
                 auto cc = designer.getCurrentColor();
                 *cc = darkbutton[1]->findColour(juce::TextButton::buttonColourId);
             }
         };
         darkbutton[1]->setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
         
         darkbutton[2].reset(new juce::TextButton(""));
         darkbutton[2]->setBounds(button[17]->getX(),button[17]->getY()+buttonHeight + yOff, buttonWidth, buttonHeight);
         contentComponent->addAndMakeVisible(darkbutton[2].get());
         darkbutton[2]->onClick = [this]{
             if(swatch){
                 selectionColour = getRandomColour();
                 selector.setCurrentColour (selectionColour);
                 setColours();
             }else{
                 auto cc = designer.getCurrentColor();
                 *cc = darkbutton[2]->findColour(juce::TextButton::buttonColourId);
             }
         };
         darkbutton[2]->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
         
         selectionColour = getRandomColour();
         selector.setCurrentColour (selectionColour);
         
         triadicPalette = getTriadicColors(selectionColour);
         for(int i = 0; i < 18; i ++){
         button[i]->setColour(juce::TextButton::buttonColourId, triadicPalette[i]);
         }
         
         int Controlwidth = (darkbutton[2]->getX() + buttonWidth) - darkbutton[0]->getX();
         
         swatchControl.reset(new juce::TextButton(""));
         swatchControl->setBounds(darkbutton[0]->getX(),darkbutton[0]->getY()+buttonHeight + yOff, Controlwidth, buttonHeight);
         contentComponent->addAndMakeVisible(swatchControl.get());
         if(swatch){
             swatchControl->setButtonText("swatch");
         }else{
             swatchControl->setButtonText("controls");
         }
         swatchControl->onClick = [this]{
             swatch = !swatch;
             if(swatch){
                 swatchControl->setButtonText("swatch");
             }else{
                 swatchControl->setButtonText("controls");
             }
         };
         //swatchControl->setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
         
     }

     ~ColourSelectorWindow()
     {
         for(int i = 0; i < numButtons; i++){
             button[i] = nullptr;
         }
         darkbutton[0] = nullptr;
         darkbutton[1] = nullptr;
         darkbutton[2] = nullptr;
         swatchControl = nullptr;
         selector.removeChangeListener (this);
     }

     void closeButtonPressed()
     {
         contentComponent = nullptr;
        
         
         delete this;
     }
     
     void setColours(){
         selectionColour = selector.getCurrentColour();
         setBackgroundColour (juce::Colours::black);
         triadicPalette = getTriadicColors(selectionColour);
         for(int i = 0; i < 18; i ++){
         button[i]->setColour(juce::TextButton::buttonColourId, triadicPalette[i]);
         }
      
     }

     bool swatch = false;
 private:
     designerValues& designer;
     juce::Colour selectionColour = juce::Colours::white;
     juce::ColourSelector selector  { juce::ColourSelector::showColourAtTop
                              | juce::ColourSelector::showSliders
                              | juce::ColourSelector::showColourspace };

     void changeListenerCallback (juce::ChangeBroadcaster* source)
     {
         if (source == &selector){
             setColours();
         
                 auto cc = designer.getCurrentColor();
                 *cc = selectionColour;
             
         }
     }
     
 
     
     std::unique_ptr<juce::Component> contentComponent;
     const int numButtons = 18;
    std::unique_ptr<juce::TextButton> button[18];
    std::unique_ptr<juce::TextButton> darkbutton[3];
     std::unique_ptr<juce::TextButton> swatchControl;
     juce::Colour getRandomColour()
     {
         juce::Random random;

         // Generate random values for red, green, and blue components
         juce::uint8 red = random.nextInt(256);    // Random value between 0 and 255
         juce::uint8 green = random.nextInt(256);  // Random value between 0 and 255
         juce::uint8 blue = random.nextInt(256);   // Random value between 0 and 255

         // Create and return the random color
         return juce::Colour(red, green, blue);
     }
     
     enum ColorModes
     {
         Triadic = 0,
         Analogous,
         RightAngles,
         Monochrome,
         Monochrome2
         // Add more color modes as needed
     };
     int colorMode = 0;
     
     std::vector<juce::Colour> triadicPalette = getTriadicColors(getRandomColour());
   
     std::vector<juce::Colour> getTriadicColors(const juce::Colour& baseColor)
     {
         std::vector<juce::Colour> triadicColors;

         // Convert the base color to HSL
         float hue, saturation, luminance;
         baseColor.getHSL(hue, saturation, luminance);

         // luminance is 0.5 to 1
         // 1 is lighter
         // 0.5 is harsher
         
         // Calculate the two additional hues for the triadic colors
         float shift[9] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
         float hues[9] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
         
         shift[0] = 0.0f;
         shift[1] = 120.0f;
         shift[2] = 240.0f;
         shift[3] = 4.0f;
         shift[4] = 30.0f;
         shift[5] = -30.0f;
         shift[6] = 8.0f;
         shift[7] = 90.0f;
         shift[8] = -180.0f;
      
         for(int i = 0; i < 9; i++){
             hues[i] = hue * 360.0f + shift[i];
             if(hues[i] > 360.0f)
                 hues[i] -= 360.0f;
             if(hues[i] < 0.0f)
                 hues[i] += 360.0f;
             
             hues[i] *= 0.00277778f;
             
             triadicColors.push_back(juce::Colour::fromHSL(hues[i], saturation, luminance,1.0f));
         }
         
         for(int i = 0; i < 9; i++){
             hues[i] = hue * 360.0f + shift[i] + 180.0f;
             if(hues[i] > 360.0f)
                 hues[i] -= 360.0f;
             if(hues[i] < 0.0f)
                 hues[i] += 360.0f;
             
             hues[i] *= 0.00277778f;
             
             triadicColors.push_back(juce::Colour::fromHSL(hues[i], saturation, luminance,1.0f));
         }

         return triadicColors;
     }

     
     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColourSelectorWindow)
 };

 
class MainComponent  : public juce::Component, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    juce::Array<juce::Component::SafePointer<juce::Component>> windows;
    
    static auto getDisplayArea()
      {
          return juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.reduced (20);
      }
    
    void closeAllWindows()
       {
           for (auto& window : windows)
               window.deleteAndZero();

           windows.clear();
          // alertWindowResult.setText ("", juce::dontSendNotification);
       }
    designerValues designer;
    
    void showDocumentWindow (bool native)
       {
        int widther = 300;
        int heighter = 700;
           auto* dw = new ColourSelectorWindow ("Color Selection", designer, juce::DocumentWindow::allButtons,widther, heighter );
           windows.add (dw);

           juce::Rectangle<int> area (0, 0, widther, heighter);

           juce::RectanglePlacement placement ((native ? juce::RectanglePlacement::xLeft
                                                 : juce::RectanglePlacement::xRight)
                                          | juce::RectanglePlacement::yTop
                                          | juce::RectanglePlacement::doNotResize);

           auto result = placement.appliedTo (area, getDisplayArea());
           dw->setBounds (result);

           dw->setResizable (true, ! native);
           dw->setUsingNativeTitleBar (native);
           dw->setVisible (true);
       }
    
    void showControlWindow (bool native)
       {
        
        int widther = 400;
        int heighter = 960;
        
           auto* dw = new ControlWindow ("Controls", designer, juce::DocumentWindow::allButtons, widther, heighter);
           windows.add (dw);

        
           juce::Rectangle<int> area (0, 0, widther, heighter);

           juce::RectanglePlacement placement ((juce::RectanglePlacement::xLeft
                                                 )
                                          | juce::RectanglePlacement::yTop
                                          | juce::RectanglePlacement::doNotResize);

           auto result = placement.appliedTo (area, getDisplayArea());
           dw->setBounds (result);

           dw->setResizable (true, ! native);
           dw->setUsingNativeTitleBar (native);
           dw->setVisible (true);
       }
    
    juce::Colour backgroundColour = juce::Colours::blue; // Example base color, you can change it to your desired color

    std::vector<juce::Colour> triadicPalette = getTriadicColors(backgroundColour);

    enum ColorModes
    {
        Triadic = 0,
        Analogous,
        RightAngles,
        Monochrome,
        Monochrome2
        // Add more color modes as needed
    };
    int colorMode = 3;
    
    enum BackgroundModes
    {
        Plain = 0,
        ThreeSquares,
        Circles,
        OutlinedCircles,
      
    };
    int backgroundMode = 3;
    
    bool centered = true;
    
    int rows = 40;
    int columns = 20;
    int centeredSize = 30;
    float outlineThickness = 3.0f;
    
    float endShift = 12.0f;
    
    float centerShift = 70.0f;
    bool incColor = true;
    
    std::vector<juce::Colour> getTriadicColors(const juce::Colour& baseColor)
    {
        std::vector<juce::Colour> triadicColors;

        // Convert the base color to HSL
        float hue, saturation, luminance;
        baseColor.getHSL(hue, saturation, luminance);

        // luminance is 0.5 to 1
        // 1 is lighter
        // 0.5 is harsher
        
        // Calculate the two additional hues for the triadic colors
        
        float firstShift = 0.0f;
        float secondShift = 0.0f;
        
        switch(colorMode){
            case Triadic:
                firstShift = 120.0f;
                secondShift = 240.0f;
                break;
            case Analogous:
                firstShift = 30.0f;
                secondShift = -30.0f;
                break;
            case RightAngles:
                firstShift = 90.0f;
                secondShift = -180.0f;
                break;
            case Monochrome:
                firstShift = 4.0f;
                secondShift = 8.0f;
                break;
            case Monochrome2:
                firstShift = 6.0f;
                secondShift = 12.0f;
                break;
        }
        float triadicHue1 = hue * 360.0f + firstShift;
        float triadicHue2 = hue * 360.0f + secondShift;
        
        if(triadicHue1 > 360.0f)
            triadicHue1 -= 360.0f;
        
        if(triadicHue2 > 360.0f)
            triadicHue2 -= 360.0f;
        
        if(triadicHue1 < 0.0f)
            triadicHue1 += 360.0f;
        
        if(triadicHue2 < 0.0f)
            triadicHue2 += 360.0f;
        
        triadicHue1 *= 0.00277778f;
        triadicHue2 *= 0.00277778f;

        // Convert the calculated hues back to RGB and create color objects
        juce::Colour triadicColor1(juce::Colour::fromHSL(triadicHue1, saturation, luminance,1.0f));
        juce::Colour triadicColor2(juce::Colour::fromHSL(triadicHue2, saturation, luminance,1.0f));

        // Add the triadic colors to the vector
        triadicColors.push_back(baseColor);
        triadicColors.push_back(triadicColor1);
        triadicColors.push_back(triadicColor2);

        return triadicColors;
    }
    
 
    // Folders for saving
    juce::File documentsFolder = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory);

     // Append the file name to the documents folder
     juce::File backgroundFolder = documentsFolder.getChildFile("Background Designer");

    juce::File projectFolder;
    juce::File sequenceFolder{projectFolder.getChildFile("sequence")};
    juce::File textFolder{projectFolder.getChildFile("text")};
    juce::File extraFolder{projectFolder.getChildFile("extra")};
    
    int width = 540;
    int height = 960;
private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
