#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (540, 960);
    showControlWindow(false);
    showDocumentWindow(false);
    startTimer(20);
}

MainComponent::~MainComponent()
{
    closeAllWindows();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (designer.colours[fillColour]);
    juce::Rectangle<int> bounds = getLocalBounds();
    float h = height;
    float w = width;
    switch(designer.gradientMode){
        case NoGradient:
          
            break;
        case RadialGradient:
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour1],     // Start color
                                          w*designer.gradientPositionsX[0], h*designer.gradientPositionsY[0],             // Start point (center)
                                          designer.colours[BackgroundColour2],   // End color
                                          w*designer.gradientPositionsX[1], h*designer.gradientPositionsY[1], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
            
            break;
        case TriRadial:
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour1],     // Start color
                                          w*designer.gradientPositionsX[0], h*designer.gradientPositionsY[0],             // Start point (center)
                                          designer.colours[BackgroundColour2],   // End color
                                          w*designer.gradientPositionsX[1], h*designer.gradientPositionsY[1], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour2].withAlpha(0.0f),     // Start color
                                          w*designer.gradientPositionsX[1], h*designer.gradientPositionsY[1],             // Start point (center)
                                          designer.colours[BackgroundColour3],   // End color
                                          w*designer.gradientPositionsX[2], h*designer.gradientPositionsY[2], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
            
            break;
            
        case QuadRadial:
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour1],     // Start color
                                          w*designer.gradientPositionsX[0], h*designer.gradientPositionsY[0],             // Start point (center)
                                          designer.colours[BackgroundColour2],   // End color
                                          w*designer.gradientPositionsX[1], h*designer.gradientPositionsY[1], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour2].withAlpha(0.0f),     // Start color
                                          w*designer.gradientPositionsX[1], h*designer.gradientPositionsY[1],             // Start point (center)
                                          designer.colours[BackgroundColour3],   // End color
                                          w*designer.gradientPositionsX[2], h*designer.gradientPositionsY[2], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
        {
            // Create a radial gradient
            juce::ColourGradient gradient(designer.colours[BackgroundColour1].withAlpha(0.0f),     // Start color
                                          w*designer.gradientPositionsX[2], h*designer.gradientPositionsY[2],             // Start point (center)
                                          designer.colours[BackgroundColour4],   // End color
                                          w*designer.gradientPositionsX[3], h*designer.gradientPositionsY[3], // End point (outer circle)
                                          true);            // Interpolated
            
            // Fill the component with the radial gradient
            g.setGradientFill(gradient);
            g.fillRect(getLocalBounds());
        }
            
            break;
    }
 
    /*
    {
        juce::Colour startColour = juce::Colours::transparentBlack;
        juce::Colour endColour = juce::Colours::black;
        
        // Define the start and end points for the gradient
        juce::Point<float> startPoint(0.5f*w, 0.5f*h);
        juce::Point<float> endPoint(w*0.5f, h);
        
        // Create a linear gradient
        juce::ColourGradient gradient(startColour, startPoint, endColour, endPoint, false);
        
        // Fill the component with the linear gradient
        g.setGradientFill(gradient);
        g.fillRect(getLocalBounds());
    }
    
    {
        juce::Colour startColour = juce::Colours::transparentBlack;
        juce::Colour endColour = juce::Colours::black;
        
        // Define the start and end points for the gradient
        juce::Point<float> startPoint(0.5f*w, 0.5f*h);
        juce::Point<float> endPoint(w*0.5f, 0.0f);
        
        // Create a linear gradient
        juce::ColourGradient gradient(startColour, startPoint, endColour, endPoint, false);
        
        // Fill the component with the linear gradient
        g.setGradientFill(gradient);
        g.fillRect(getLocalBounds());
    }
    
    {
        juce::Colour startColour = juce::Colours::transparentBlack;
        juce::Colour endColour = juce::Colours::black;
        
        // Define the start and end points for the gradient
        juce::Point<float> startPoint(w*0.5f, 0.5f*h);
        juce::Point<float> endPoint(0.0f, 0.5f*h);
        
        // Create a linear gradient
        juce::ColourGradient gradient(startColour, startPoint, endColour, endPoint, false);
        
        // Fill the component with the linear gradient
        g.setGradientFill(gradient);
        g.fillRect(getLocalBounds());
    }
    
    {
        juce::Colour startColour = juce::Colours::transparentBlack;
        juce::Colour endColour = juce::Colours::black;
        
        // Define the start and end points for the gradient
        juce::Point<float> startPoint(w*0.5f, 0.5f*h);
        juce::Point<float> endPoint(w, 0.5f*h);
        
        // Create a linear gradient
        juce::ColourGradient gradient(startColour, startPoint, endColour, endPoint, false);
        
        // Fill the component with the linear gradient
        g.setGradientFill(gradient);
        g.fillRect(getLocalBounds());
    }
     */
   
//    g.setFont (juce::Font (16.0f));
//    g.setColour (juce::Colours::white);
//    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::timerCallback()
{
 
    repaint();
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

/*
 
 switch(backgroundMode){
     case Plain:
         g.fillAll(backgroundColour);
         break;
     case ThreeSquares:
     {
         juce::Rectangle<int> squares[3];
         
         int x = 0;
         int y = 0;
         int height = bounds.getHeight();
         int width = bounds.getWidth() * 0.33333333f;
         
         triadicPalette = getTriadicColors(backgroundColour);
         for(int i = 0; i < 3; i++){
             squares[i].setBounds(x, y, width, height);
             x += width;
             g.setColour(triadicPalette[i]);
             g.fillRect(squares[i]);
         }
     }
         break;
     case Circles:
     {
         int numEntities = rows * columns;
         g.fillAll(juce::Colours::white);
         g.setColour(backgroundColour);
         if(centered){
             juce::Colour baseColor = backgroundColour;
             float incSize =  endShift / (float)numEntities;
             incSize *= 0.00277778f;
             float hue, saturation, luminance;
             baseColor.getHSL(hue, saturation, luminance);
             
             for(int i = 0; i < numEntities; i++){
                 hue += incSize;
                 if(incSize > 1.0f)
                     hue -= 1.0f;
                 
                 g.setColour(juce::Colour::fromHSL(hue, saturation, luminance,1.0f));
                 
                 g.fillEllipse(position::getCenter(position::getPositionInRectLinear(bounds, i, rows, columns),centeredSize,centeredSize).toFloat());
                 
             }
         }else{
             for(int i = 0; i < numEntities; i++){
                 g.fillEllipse(position::getPositionInRectLinear(bounds, i, rows, columns).toFloat());
                 
             }
         }
     }
         break;
     case OutlinedCircles:
     {
         int numEntities = rows * columns;
         g.fillAll(juce::Colours::white);
         g.setColour(backgroundColour);
         if(centered){
             juce::Colour baseColor = backgroundColour;
             float incSize =  endShift / (float)numEntities;
             incSize *= 0.00277778f;
             float hue, saturation, luminance;
             baseColor.getHSL(hue, saturation, luminance);
             
             for(int i = 0; i < numEntities; i++){
                 hue += incSize;
                 if(hue > 1.0f)
                     hue -= 1.0f;
                 
                 float invHue = ((hue * 360.0f) + centerShift) * 0.00277778f;
                 if(invHue > 1.0f)
                     invHue -= 1.0f;
                 
                 g.setColour(juce::Colour::fromHSL(invHue, saturation, luminance,1.0f));
                 
                 g.fillEllipse(position::getCenter(position::getPositionInRectLinear(bounds, i, rows, columns),centeredSize,centeredSize).toFloat());
                 
                 g.setColour(juce::Colour::fromHSL(hue, saturation, luminance,1.0f));
                 
                 g.drawEllipse(position::getCenter(position::getPositionInRectLinear(bounds, i, rows, columns),centeredSize,centeredSize).toFloat(),outlineThickness);
                 
             }
         }else{
             for(int i = 0; i < numEntities; i++){
                 g.drawEllipse(position::getPositionInRectLinear(bounds, i, rows, columns).toFloat(), outlineThickness);
                 
             }
         }
     }
         break;
 }
 */
