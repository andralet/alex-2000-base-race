void InitAudio(int &driver, mpg123_handle *(&mh), size_t &buffer_size, unsigned char *(&buffer)) {
    int err = 0;
    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
}

void ShutdownAudio(mpg123_handle *(&mh), unsigned char *(&buffer)) {
    free(buffer);
    buffer = NULL;
    mpg123_close(mh);
    mpg123_delete(mh);
    mh = NULL;
    mpg123_exit();
    ao_shutdown();
}

bool StopPlayingFile(void) {
    return (FINISH_DAEMON || SWITCH_DAEMON_TRACK);
}

void PlayFile(const char *filename, int &driver, mpg123_handle *(&mh), size_t &buffer_size, unsigned char *(&buffer)) {
    ao_sample_format format;
    int channels, encoding;
    long rate;
    size_t done;

    /* open the file and get the decoding format */
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    ao_device *dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (!StopPlayingFile() && mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
		ao_play(dev, (char *) ((void *) buffer), done); // yes, I know, it's not very good

    /* clean up */
    ao_close(dev);
}
