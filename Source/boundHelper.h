#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace position {

template <class T>
juce::Rectangle<T> getPosition(T x, T y, T width, T height, T row, T column, T rows, T columns, bool reduced = false){
T columnWidth = width/columns;
T rowHeight = height/rows;
T boxX = (columnWidth*(column-1))+x;
T boxY = (rowHeight*(row-1))+y;
    if(reduced){
        columnWidth = columnWidth - 1;
        rowHeight = rowHeight - 1;
    }
    
return juce::Rectangle<T>(boxX,boxY,columnWidth,rowHeight);
}
    
template <class T>
juce::Rectangle<T> getPositionInRect(juce::Rectangle<T> parentBox, T row, T column, T rows, T columns, bool reduced = false){
    T x = parentBox.getX();
    T y = parentBox.getY();
    T width = parentBox.getWidth();
    T height = parentBox.getHeight();
T columnWidth = width/columns;
T rowHeight = height/rows;
T boxX = (columnWidth*(column-1))+x;
T boxY = (rowHeight*(row-1))+y;
    if(reduced){
        columnWidth = columnWidth - 1;
        rowHeight = rowHeight - 1;
    }
    
return juce::Rectangle<T>(boxX,boxY,columnWidth,rowHeight);
}

template <class T>
juce::Rectangle<T> getPositionInRectLinear(juce::Rectangle<T> parentBox, T input, T rows, T columns, bool reduced = false){
    
//    T index = input + 1;
    T row = 1;
    float rower = ((input)/ columns);
    for(int i = 0; i < (rows); i++){
        if(rower > i){
            row += 1;
        }
    }
    T column = (input % columns)+1;

    
    T x = parentBox.getX();
    T y = parentBox.getY();
    T width = parentBox.getWidth();
    T height = parentBox.getHeight();
T columnWidth = width/columns;
T rowHeight = height/rows;
T boxX = (columnWidth*(column-1))+x;
T boxY = (rowHeight*(row-1))+y;
    if(reduced){
        columnWidth = columnWidth - 1;
        rowHeight = rowHeight - 1;
        
        
    }
    
return juce::Rectangle<T>(boxX,boxY,columnWidth,rowHeight);
}

template <class T>
juce::Rectangle<T> getThirdRect(juce::Rectangle<T> parentBox, T column, bool reduced = false){
    T x = parentBox.getX();
    T y = parentBox.getY();
    T width = parentBox.getWidth();
    T height = parentBox.getHeight();
    T width2 = width * 0.2f;
    T width8 = width * 0.8f;
    T width6 = width * 0.6f;
    
    T xer = x;// + width6;
    T outwidth = width;
    
    if(column == 1){
        if(reduced){
            height = height - 1;
            width2 = width2 - 1;
            width8 = width8 - 1;
            width6 = width6 - 1;
        }
        outwidth = width2;
    }
    else if(column == 2){
    xer = x + width2;
        if(reduced){
            width = width - 1;
            height = height - 1;
            width2 = width2 - 1;
            width8 = width8 - 1;
            width6 = width6 - 1;
        }
        outwidth = width6;
    }else if(column == 3){
    xer = x + width8;
        if(reduced){
            width = width - 1;
            height = height - 1;
            width2 = width2 - 1;
            width8 = width8 - 1;
            width6 = width6 - 1;
        }
        outwidth = width2;
    }
    return juce::Rectangle<T>(xer,y,outwidth,height);
}

template <class T>
juce::Rectangle<T> getUpDownRect(juce::Rectangle<T> parentBox, T column, bool reduced = false){
    T x = parentBox.getX();
    T y = parentBox.getY();
    T width = parentBox.getWidth();
    T height = parentBox.getHeight();
    T width2 = width * 0.2f;
    T width8 = width * 0.8f;

    
    T xer = x;// + width6;
    T outwidth = width;
    
    if(column == 1){
        if(reduced){
            height = height - 1;
            width2 = width2 - 1;
            width8 = width8 - 1;
      
        }
        outwidth = width8;
    }
    else if(column == 2){
    xer = x + width8;
        if(reduced){
            width = width - 1;
            height = height - 1;
            width2 = width2 - 1;
            width8 = width8 - 1;
 
        }
        outwidth = width2;
    }
    return juce::Rectangle<T>(xer,y,outwidth,height);
}

template <class T>
juce::Rectangle<T> verticalSplit(juce::Rectangle<T> parentBox, T column, bool reduced = false){
    T x = parentBox.getX();
    T y = parentBox.getY();
    T width = parentBox.getWidth();
    T height = parentBox.getHeight();
    T height2 = height * 0.5f;

   
    
    if(column == 1){
        if(reduced){
            width = width - 1;
            height2 = height2 - 1;
        }
    return juce::Rectangle<T>(x,y,width,height2);
    }
    else{
    T yer = y + height2;
        if(reduced){
            width = width - 1;
            height2 = height2 - 1;
        }
    return juce::Rectangle<T>(x,yer,width,height2);
    }
 
}

template <class T>
    juce::Rectangle<T> getCenter(juce::Rectangle<T> parentBox, T boxWidth, T boxHeight, T xOffset = 0, T yOffset = 0){
        T centerOffsetX = (((parentBox.getWidth()*0.5) - (boxWidth*0.5)) + parentBox.getX()) + xOffset;
        T centerOffsetY = (((parentBox.getHeight()*0.5) - (boxHeight*0.5))+ parentBox.getY()) + yOffset;
    return juce::Rectangle<T>(centerOffsetX,centerOffsetY,boxWidth,boxHeight);
    }
  


template <class T>
    juce::Rectangle<T> getUnder(juce::Rectangle<T> parentBox, T height, T yOffset = 0){
        T newY = parentBox.getY()+parentBox.getHeight() + yOffset;
    return juce::Rectangle<T>(parentBox.getX(),newY,parentBox.getWidth(),height);
    }

template <class T>
    juce::Rectangle<T> getTopInside(juce::Rectangle<T> parentBox, T height, T yOffset = 0){
        T newY = parentBox.getY() + yOffset;
    return juce::Rectangle<T>(parentBox.getX(),newY,parentBox.getWidth(),height);
    }

template <class T>
    T getCenterOffset(T length, T size){
        return (length*0.5)-(size*0.5);
    }

template <class T>
    void printNumbers(juce::String name, juce::Rectangle<T> parentBox){
        T x = parentBox.getX();
        T y = parentBox.getY();
        T width = parentBox.getWidth();
        T height = parentBox.getHeight();
        DBG(name << x << "," << y << "," << width << "," << height);
    }

template <class T>
juce::Rectangle<T> offsetX(juce::Rectangle<T> parentBox, T offset){
return juce::Rectangle<T>(parentBox.getX()+offset,parentBox.getY(),parentBox.getWidth(),parentBox.getHeight());
    }

template <class T>
juce::Rectangle<T> offsetY(juce::Rectangle<T> parentBox, T offset){
return juce::Rectangle<T>(parentBox.getX(),parentBox.getY()+offset,parentBox.getWidth(),parentBox.getHeight());
    }


enum{
    left = 0,
    right,
    top,
    bottom
};

template <class T>
juce::Rectangle<T> blendBox(juce::Rectangle<T> smallBox, juce::Rectangle<T> largeBox, T blend){
    
    T x = ((largeBox.getX()-smallBox.getX()) * blend) + smallBox.getX();
    T y = ((largeBox.getY()-smallBox.getY()) * blend) + smallBox.getY();
    T width = ((largeBox.getWidth()-smallBox.getWidth()) * blend) + smallBox.getWidth();
    T height = ((largeBox.getHeight()-smallBox.getHeight()) * blend) + smallBox.getHeight();
return juce::Rectangle<T>(x,y,width,height);
    }

template <class T>
juce::Point<T> blendPoint(juce::Point<T> smallPoint, juce::Point<T> largePoint, T blend){
    
    T x = ((largePoint.getX()-smallPoint.getX()) * blend) + smallPoint.getX();
    T y = ((largePoint.getY()-smallPoint.getY()) * blend) + smallPoint.getY();

return juce::Point<T>(x,y);
    }

template <class T>
juce::Line<T> getLine(juce::Rectangle<T> parentBox, int position){
    juce::Point<T> first;
    juce::Point<T> last;
    switch (position) {
        case left:
            first = parentBox.getTopLeft();
            last = parentBox.getBottomLeft();
            break;
        case right:
            first = parentBox.getTopRight();
            last = parentBox.getBottomRight();
            break;
        case top:
            first = parentBox.getTopLeft();
            last = parentBox.getTopRight();
            break;
        case bottom:
            first = parentBox.getBottomLeft();
            last = parentBox.getBottomRight();
            break;
            
        default:
            break;
            
          
    }
    return juce::Line<T>(first,last);
            
    }
}
