#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string: ");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);

    printf("Enter number of frames: ");
    scanf("%d",&f);

    int frames[f], freq[f];
    for(int i=0;i<f;i++){
        frames[i]=-1; // empty frame
        freq[i]=0;    // frequency counter
    }

    int faults=0;

    printf("\nPage\tFrames\n-----------------\n");

    for(int i=0;i<n;i++){
        int page=pages[i], found=0;

        // Check if page is already in frame
        for(int j=0;j<f;j++){
            if(frames[j]==page){
                freq[j]++; // increment usage frequency
                found=1;
                break;
            }
        }

        if(!found){
            faults++;
            int replace_index=0;

            // If empty frame available, use it
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    replace_index=j;
                    break;
                }
            }

            // If all frames full, find MFU page
            if(frames[replace_index]!=-1){
                int max=freq[0];
                replace_index=0;
                for(int j=1;j<f;j++){
                    if(freq[j]>max){
                        max=freq[j];
                        replace_index=j;
                    }
                }
            }

            frames[replace_index]=page;
            freq[replace_index]=1; // first use
        }

        // Display current frames
        printf("%d\t",page);
        for(int j=0;j<f;j++){
            if(frames[j]!=-1) printf("%d ",frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("-----------------\nTotal Page Faults = %d\n",faults);
    return 0;
}
