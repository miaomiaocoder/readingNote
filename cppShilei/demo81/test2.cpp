#include <iostream>
#include <memory>

using namespace std;

class VideoSite {
   public:
    virtual void freeMovie() = 0;    // 免费电影
    virtual void vipMovie() = 0;     // vip电影
    virtual void ticketMovie() = 0;  // 用券观看电影
};

class FixBugVideoSite : public VideoSite {
    virtual void freeMovie() {  // 免费电影
        cout << "观看免费电影" << endl;
    }
    virtual void vipMovie() { cout << "观看vip电影" << endl; }
    virtual void ticketMovie() { cout << "用券观看电影" << endl; }
};

class FreeVideoSitProxy : public VideoSite {
   public:
    FreeVideoSitProxy() { pVideo = new FixBugVideoSite(); }
    ~FreeVideoSitProxy() { delete pVideo; }

    virtual void freeMovie() { pVideo->freeMovie(); }
    virtual void vipMovie() {
        cout << "您目前只是普通游客，需要升级成VIP，才能观看VIP电影" << endl;
    }
    virtual void ticketMovie() {
        cout << "您目前没有券，需要购买电影券，才能观看电影" << endl;
    }

   private:
    VideoSite* pVideo;
};

class VipVideoSitProxy : public VideoSite {
   public:
    VipVideoSitProxy() { pVideo = new FixBugVideoSite(); }
    ~VipVideoSitProxy() { delete pVideo; }

    virtual void freeMovie() { pVideo->freeMovie(); }
    virtual void vipMovie() { pVideo->vipMovie(); }
    virtual void ticketMovie() {
        cout << "您目前没有券，需要购买电影券，才能观看电影" << endl;
    }

   private:
    VideoSite* pVideo;
};

void watchMovie(unique_ptr<VideoSite>& ptr) {
    ptr->freeMovie();
    ptr->vipMovie();
    ptr->ticketMovie();
}

int main() {
    unique_ptr<VideoSite> p1(new FreeVideoSitProxy());
    unique_ptr<VideoSite> p2(new VipVideoSitProxy());

    watchMovie(p1);

    cout << "............." << endl;

    watchMovie(p2);

    return 0;
}