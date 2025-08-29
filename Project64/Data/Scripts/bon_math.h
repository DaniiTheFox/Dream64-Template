// ------------------ Helpers suavizado ------------------
float approachf(float cur,float goal,float step){
    float d = goal - cur;
    if (fabsf(d) <= step) return goal;
    return cur + (d>0? step : -step);
}

float approachAngle(float cur,float goal,float step){
    float d = fmodf(goal - cur + 540.0f, 360.0f) - 180.0f;
    if (fabsf(d) <= step) return goal;
    return cur + (d>0? step : -step);
}

long long currentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

float smoothAngle(float current, float target, float speed) {
    float difference = fmodf(target - current + 540.0f, 360.0f) - 180.0f;
    if (fabsf(difference) <= speed) return target;
    return current + (difference > 0 ? speed : -speed);
}