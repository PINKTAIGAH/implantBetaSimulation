#ifndef TIME_RANGE_MANAGER_LOCAL_H
#define TIME_RANGE_MANAGER_LOCAL_H

#include <vector>


struct TimeRange {
  double  start;
  double  end;
  int    posX;
  int    posY;

  bool contains(double currentTime, int posX, int posY, int posRange) const;

  bool operator<(const TimeRange& other) const;
};

class TimeRangeManagerLocal {
  public:

    TimeRangeManagerLocal(int positionThreshold=5); 

    void addRange(double start, double end, int posX, int posY);

    // Check if a time is within any merged range
    bool contains(double time, int posX, int posY);

  private:
    int                     positionRange;
    std::vector<TimeRange>  ranges;

};

#endif